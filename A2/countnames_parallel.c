/**
 * Description: This module takes user txt files and counts the names and their occurrences from all the given files. This module uses Process ID and Forks to perform the action.
 * Author names: Mark Ibarra
 * Author emails: mark.ibarra@sjsu.edu
 * Last modified date: 3/9/2023
 * Creation date: 3/9/2023
 **/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {

    char str[100];
    char *names[100];
    //char copyNames[100][30]; //not needed as
    int countTotal = 0;
    int numberLines = 0;
    int occur[100] = {0};
    //int duplicate; not needed as finding duplcate logic has changed
    int fileCount = argc -1;
    int fd[2];
    pid_t p;
    int i, j;

    //error message to let user know how to use the program
    if (argc < 2) {
        printf("Wrong input. Please use as follows...\n""""./countnames_parallel [file.txt] [file.txt]...[file.txt]\n""");
        return 1;
    }

    for (i = 0; i < fileCount; i++){

        // Reads the amount of files given in terminal
        FILE *fp = fopen(argv[i+1], "r");

        // If file does not exist or no txt file is named, this error will execute
        if (fp == NULL) {
            fprintf(stderr,"Cannot open file\n");
            return 1;
        }
        // Sets numberLines to zero when a new file is loaded
        numberLines = 0;
        /**
            * This while loop reads lines from the given text file by using fgets function. This
            * begins writing content to stdout.
            **/
        while(fgets (str, 30, fp) != NULL) {

            numberLines++;

            // This line of code removes newline characters and replaces it with a null terminator.
            str[strcspn(str, "\n")] = '\0';

            // If a line in the given text is empty, a warning print will execute along with what file it comes from.
            if (str[0] == '\0') {
                printf("Warning - Line %d is empty in file %s.\n", numberLines, argv[i+1]);
            }

            // Checks if the name being read is already in the array. setting nameIndex to -1
            int nameIndex = -1;
            //numberLines == 0;
            for (j = 0; j < countTotal; j++) {
                if (strcmp(names[j], str) == 0) {
                    nameIndex = j;
                    break;
                }
            }

            if (nameIndex >= 0) {
                // If name already exists, increment occurrence
                occur[nameIndex]++;
            } else {
                // else if it's not in array, add name to the array
                names[countTotal] = strdup(str);
                occur[countTotal]++;
                countTotal++;
            }
        }

        fclose(fp);
    }

    // Creates pipe and checks if an error occurs
    if (pipe(fd) == -1) {
        printf("Error: unable to create pipe\n");
        exit(1);
    }

    // Creates p to fork process
    p = fork();

    // If fork errors out, it'll print error statement
    if (p < 0) {
        printf("Error: unable to fork process\n");
        exit(1);
    }

    if (p == 0) { // Entering child process
        close(fd[1]); // Closes write end of the pipe

        /**
         * A while loop thats reads from file descriptor and places it into a buffer.
         * The null terminator is added to the end of the buffer to make it end as a string
         * the for loop then goes through the names array and compares them to the information in buffer.
         * When a match is found, the corresponding element for occurrenceis incremented
        **/
        char buf[30];
        int bytesRead = 0;
        while ((bytesRead = read(fd[0], buf, 30)) > 0) {
            buf[bytesRead] = '\0';
            for (i = 0; i < countTotal; i++) {
                if ((strcmp(names[i], buf) == 0) && (strcmp(names[i], buf) != '\0')) {
                    occur[i]++;
                    break;
                }
            }
        }

        // For loop prints a full name and its occurrences
        for (i = 0; i < countTotal; i++) {
             if(names[i][0] != '\0'){
                printf("%s: %d\n", names[i], occur[i]);
            }
        }
        //Closes read end of the pipe
//         close(fd[0]);

    } else { // Parent process
        close(fd[0]); // Closes read end of the pipe

        // Write the names to pipe
        for (i = 0; i < countTotal; i++) {
            write(fd[1], names[i], strlen(names[i]));
        }

        close(fd[1]); // Closes write end of the pipe
        wait(NULL);
    }

    // For loop to free up memory
    for (i = 0; i < countTotal; i++) {
        free(names[i]);
    }

    return 0;
}
