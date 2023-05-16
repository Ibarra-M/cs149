/**
 * Description: This module takes user txt files and counts the names and their occurrences from all the given files.
 * This module uses a threaded method to count the names, ratheer than a parallel manner.
 * Author names: Mark Ibarra
 * Author emails: mark.ibarra@sjsu.edu
 * Creation date: 5/15/2023
 **/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <pthread.h>
#include <stdbool.h>
#include <time.h>

// Variables changed to global variables
char str[100];
char *names[100];
int countTotal = 0;
int numberLines = 0;
int occur[100] = {0};
int fileCount = 0;
pthread_mutex_t logMutex = PTHREAD_MUTEX_INITIALIZER;

pthread_mutex_t tlock1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t tlock2 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t tlock3 = PTHREAD_MUTEX_INITIALIZER;

void* thread_runner(void*);

pthread_t tid1, tid2;

struct THREADDATA_STRUCT {
    pthread_t creator;
};

typedef struct THREADDATA_STRUCT THREADDATA;

THREADDATA* p = NULL;

int logIndex = 1;
int *logip = &logIndex;

struct NAME_STRUCT {
    char name[30];
    int count;
};

typedef struct NAME_STRUCT THREAD_NAME;

THREAD_NAME names_counts[100];

struct NAME_NODE {
    THREAD_NAME name_count;
    struct NAME_NODE *next;
};


pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

//Function to print log messages
void logprint(char *message) {
    time_t now = time(NULL);
    struct tm *timeinfo = localtime(&now);

    pthread_mutex_lock(&logMutex);
    printf("Logindex %d, thread %ld, PID %d, %02d/%02d/%04d %02d:%02d:%02d %s: %s\n",
           logIndex, pthread_self(), getpid(),
           timeinfo->tm_mday, timeinfo->tm_mon + 1, timeinfo->tm_year + 1900,
           timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec,
           (timeinfo->tm_hour < 12) ? "am" : "pm", message);
    logIndex++;
    pthread_mutex_unlock(&logMutex);
}

//Countnames has been changed into a function thats uses threads to count the names in all given files
void* countNames(void* arg) {
    int index = *(int*)arg;
    FILE *fp = fopen(names[index], "r");
    char *fileName = names[index];

    if (fp == NULL) {
        logprint("failed to open file");
        pthread_exit(NULL);
    }
    logprint("opened file");

    if (fp == NULL) {
        pthread_mutex_lock(&mutex);
        fprintf(stderr, "Cannot open file: %s\n", fileName);
        pthread_mutex_unlock(&mutex);
        return NULL;
    }

    numberLines = 0;
    while (fgets(str, 30, fp) != NULL) {
        numberLines++;

        str[strcspn(str, "\n")] = '\0';

        if (str[0] == '\0') {
            pthread_mutex_lock(&mutex);
            printf("Warning - Line %d is empty in file %s.\n", numberLines, fileName);
            pthread_mutex_unlock(&mutex);
        }

        int nameIndex = -1;
        for (int j = 0; j < countTotal; j++) {
            if (strcmp(names[j], str) == 0) {
                nameIndex = j;
                break;
            }
        }

        if (nameIndex >= 0) {
            pthread_mutex_lock(&mutex);
            occur[nameIndex]++;
            pthread_mutex_unlock(&mutex);
        } else {
            pthread_mutex_lock(&mutex);
            names[countTotal] = strdup(str);
            occur[countTotal]++;
            countTotal++;
            pthread_mutex_unlock(&mutex);
        }
    }

    fclose(fp);
    pthread_exit(NULL);
}


int main(int argc, char *argv[]) {

    fileCount = argc - 1;
    printf("==================== Log Messages ====================\n");

    //Makes sure a file has been passed to the program
    if (fileCount < 1) {
        printf("Wrong input. Please use as follows:\n"
               "./countnames_threads [file.txt] [file.txt]...[file.txt]\n");
        return 1;
    }

    //Copies file names from argv to names array
    for (int i = 0; i < fileCount; i++) {
        names[i] = strdup(argv[i + 1]);
    }

    pthread_t threads[fileCount];
    int threadArgs[fileCount];

    //Create threads to process each file
    for (int i = 0; i < fileCount; i++) {
        threadArgs[i] = i;
        if (i == 0){
            printf("create first thread\n");
            if (pthread_create(&threads[i], NULL, countNames, &threadArgs[i]) != 0) {
                fprintf(stderr, "Failed to create thread for file %s\n", names[i]);
            }
        } else if(i == 1){
                printf("create second thread\n");
                if (pthread_create(&threads[i], NULL, countNames, &threadArgs[i]) != 0) {
                fprintf(stderr, "Failed to create thread for file %s\n", names[i]);
                }
            }
    }

    //Wait for first thread to finish
    printf("Wait for first thread to exit\n");
    pthread_join(threads[0], NULL);
    printf("First thread exited\n");

    //Wait for second thread to finish
    printf("Wait for second thread to exit\n");
    pthread_join(threads[1], NULL);
    printf("Second thread exited\n");

    printf("\n===================== Name Counts ====================\n");

    //Print all the name occurrences
    for (int i = 0; i < countTotal; i++) {
        if (names[i][0] != '\0') {
            printf("%s: %d\n", names[i], occur[i]);
        }
    }

    //For loop to free allocated memory
    for (int i = 0; i < countTotal; i++) {
        free(names[i]);
    }

    return 0;
}
