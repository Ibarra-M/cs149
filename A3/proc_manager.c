/**
 * Description: This module reads arguemnts from the command line. It then creates an output text, and after child     * PID, that writes the execution into the file. The program also logs errors into an error file.
 * Author names: Mark Ibarra
 * Author emails: mark.ibarra@sjsu.edu
 * Last modified date: 3/24/2023
 * Creation date: 3/24/2023
 **/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>

#define MAX_ARGS 100
#define MAX_CMD_LEN 30

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

            // logs finished message that child process has finished
            dprintf(outputFD,"Finished child %d pid of parent %d\n", p, getppid());

            if (WIFEXITED(status)) { // if child process exits normally, it'll print the proper code
                // logs exit code to the error file
                dprintf(errorFD, "Exited with exitcode = %d\n", WEXITSTATUS(status));
            } else if (WIFSIGNALED(status)) { // if child process is terminated by signal, proper message will print
                // logs signal to the error file
                dprintf(errorFD, "Killed with signal %d\n", WTERMSIG(status));
            }

        // close all open files
        close(outputFD);
        close(errorFD);

        }
    }

    return 0;
}
