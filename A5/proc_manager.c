/**
 * Description: This module reads arguemnts from the command line. It then processes the information into a hash function. It then prints out the process from the hash to a file. Additionally, the time it takes for each process to finish is tracked.
 * Author names: Mark Ibarra
 * Author emails: mark.ibarra@sjsu.edu
 * Last modified date: 4/29/2023
 * Creation date: 4/29/2023
 **/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>
#include <time.h>

#define MAX_ARGS 100
#define MAX_CMD_LEN 30

#define HASH_TABLE_SIZE 100

// struct to help process the proper varibles
typedef struct ProcessInfo {
    pid_t pid;
    int index;
    char command[MAX_CMD_LEN];
    struct timespec startTime;
    struct timespec finishTime;
    struct ProcessInfo* next;
} ProcessInfo;

ProcessInfo* hashTable[HASH_TABLE_SIZE];

unsigned long hash(const char* str) {
    unsigned long hash = 0;
    int c;
    while ((c = *str++)) {
        hash += (hash * 33) +c;
    }
    return hash % HASH_TABLE_SIZE;
}

// creates and returns a pointer to dynamically allocated ProcessInfo.
ProcessInfo* create_process_info(pid_t pid, int index, const char* command, const struct timespec* startTime) {
    ProcessInfo* info = (ProcessInfo*) malloc(sizeof(ProcessInfo));

    if (info == NULL) {
        printf("Error: out of memory\n");
        exit(1);
    }

    info->pid = pid;
    info->index = index;
    strcpy(info->command, command);
    info->startTime.tv_sec = startTime->tv_sec;
    info->startTime.tv_nsec = startTime->tv_nsec;
    info->finishTime.tv_sec = 0;
    info->finishTime.tv_nsec = 0;
    info->next = NULL;

    return info;
}

void insert_process_info(ProcessInfo* info) {
    unsigned long index = hash( info->command );
    ProcessInfo *current = hashTable[index];
    if (current == NULL) {
        hashTable[index] = info;
    } else {
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = info;
    }
}

ProcessInfo* find_process_info(const char* command) {
    unsigned long index = hash(command);
    ProcessInfo* current = hashTable[index];
    while (current != NULL && strcmp(current->command, command) != 0) {
        current = current->next;
    }
    return current;
}

void print_elapsed_time(ProcessInfo* process) {
    struct timespec elapsed_time;

    elapsed_time.tv_sec = process->finishTime.tv_sec - process->startTime.tv_sec;
    elapsed_time.tv_nsec = process->finishTime.tv_nsec - process->startTime.tv_nsec;

    // Handle the case where finishTime.tv_nsec is smaller than startTime.tv_nsec
    if (elapsed_time.tv_nsec < 0) {
        elapsed_time.tv_sec--;
        elapsed_time.tv_nsec += 1000000000;
    }

    printf("Process %d finished in %ld.%09ld seconds\n", process->index, elapsed_time.tv_sec, elapsed_time.tv_nsec);
}

int main(){

    char userCommands[MAX_CMD_LEN];
    char *args[MAX_ARGS];
    int commandCount = 0;
    char outputFile[20];
    char errorFile[20];
    int status;
    int outputFD;
    int errorFD;
    pid_t p;
    int i;
    double elapsed;


    // reads commands until EOF signal is given ctrl + d
    while(fgets(userCommands, MAX_CMD_LEN, stdin) != NULL){

        commandCount++;

        // This line of code removes newline characters and replaces it with a null terminator.
        userCommands[strcspn(userCommands, "\n")] = '\0';

        // while loop to tokenize userCommands into individual arguments and stores them in args
        i = 0;
        args[i] = strtok(userCommands, " ");
        while (args[i] != NULL && i < MAX_ARGS - 1) {
            i++;
            args[i] = strtok(NULL, " ");
        }
        args[i] = NULL; // last argument must be NULL

        // creates output and error files for child process using PID of the child process
        sprintf(outputFile, "%d.out", getpid());
        sprintf(errorFile, "%d.err", getpid());

        // start tracking time
        struct timespec start, finish;
        clock_gettime(CLOCK_MONOTONIC, &start);

        // fork child process creation
        p = fork();

        // If fork errors out, it'll print error statement
        if (p < 0) {
            printf("Error: unable to fork process\n");
            exit(1);
        }

        if (p == 0) { // Entering child process
            // creates output and error files for child process using PID of the child process
            sprintf(outputFile, "%d.out", getpid());
            sprintf(errorFile, "%d.err", getpid());

            /**
            * opens outputFile and errorFile in write-only mode. If file is not found, it'll create the files. Files
            * appends the files to the end of the file. The file is opened with 0777 which is read and
            * write permissions.
            **/
            outputFD = open(outputFile, O_WRONLY | O_CREAT | O_APPEND, 0777);
            errorFD = open(errorFile, O_WRONLY | O_CREAT | O_APPEND, 0777);

            // logs starting command message
            dprintf(outputFD, "Starting command %d: child %d pid of parent %d\n",commandCount, getpid(), getppid());

            struct timespec start, finish;
            clock_gettime(CLOCK_MONOTONIC, &start);
            //fprintf(outputFD, "Start Time: %ld.%ld seconds\n", startTime.tv_sec, startTime.tv_nsec);

            // redirects outputFD and errorFD to files
            dup2(outputFD, STDOUT_FILENO);
            dup2(errorFD, STDERR_FILENO);

            execvp(args[0],args);

            // if execvp returns, it must have failed
            fprintf(stderr, "Failed to execute command %s\n", args[0]);
            exit(2);

        } else if (p > 0) { // Parent process turn

            // create a new output and error files using child PID
            sprintf(outputFile, "%d.out", p);
            sprintf(errorFile, "%d.err", p);

            // open files for parent process
            outputFD = open(outputFile, O_WRONLY | O_CREAT | O_APPEND, 0777);
            errorFD = open(errorFile, O_WRONLY | O_CREAT | O_APPEND, 0777);

            // wait for the child process to finish
            wait(&status);
	    	    
            ProcessInfo* info = create_process_info(p, commandCount, args[0], &start);
	    
	    // set finish time of process
            info->finishTime.tv_sec = finish.tv_sec;
            info->finishTime.tv_nsec = finish.tv_nsec;

            insert_process_info(info);
	    
	    // get finished time
            clock_gettime(CLOCK_MONOTONIC, &finish);

            elapsed = (finish.tv_sec - start.tv_sec);
            // logs finished message that child process has finished
            dprintf(outputFD,"Finished child %d pid of parent %d\n", p, getppid());
            dprintf(outputFD,"Finished at %ld, runtime duration %.f\n", finish.tv_sec, elapsed);

            if (WIFEXITED(status)) { // if child process exits normally, it'll print the proper code
                // logs exit code to the error file
                dprintf(errorFD, "Exited with exitcode = %d\n", WEXITSTATUS(status));
            } else if (WIFSIGNALED(status)) { // if child process is terminated by signal, proper message will print
                // logs signal to the error file
                dprintf(errorFD, "Killed with signal %d\n", WTERMSIG(status));
            }

            // check if the process took more than 2 seconds
            if ((finish.tv_sec - start.tv_sec) > 2 ||
                ((finish.tv_sec - start.tv_sec) == 2 && (finish.tv_sec - start.tv_sec) > 0)) {
                dprintf(errorFD, "Spawning too fast\n");
            }

        // close all open files
        close(outputFD);
        close(errorFD);

        }
    }

    return 0;
}
