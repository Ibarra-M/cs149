/**
 * Description:
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

int main(){
    char userCommands[32];
    int commandCount = 0;
    char *args[100];
    char outputFile[20];
    char errorFile[20];
    int status;
    int outputFD;
    int errorFD;
    //int fd[2];
    pid_t p;
    int ;

    while(fgets(userCommands, 32, stdin) != NULL){

        commandCount++;

        // This line of code removes newline characters and replaces it with a null terminator.
        userCommands[strcspn(userCommands, "\n")] == '0';

        args[0] = strtok(userCommands, " \n");

        if (args[0] == NULL) {
            continue;
        }

        // Creates output and error files for child process using PID of the child process
        sprintf(outputFile, "%d.out", getpid());
        sprintf(errorFile, "%d.err", getpid());

        /**
        * opens outputFile and errorFile in write-only mode. If file is not found, it'll create the files. Files
        * appends the files to the end of the file. The file is opened with 0777 which is read and
        * write permissions.
        **/
        outputFD = open(outputFile, O_WRONLY | O_CREAT | O_APPEND, 0777);
        errorFD = open(errorFile, O_WRONLY | O_CREAT | O_APPEND, 0777);

        // fork creation
        p = fork();

        // If fork errors out, it'll print error statement
        if (p < 0) {
            printf("Error: unable to fork process\n");
            exit(1);
        }

        if (p == 0) { // Entering child process

            dup2(outputFD, STDOUT_FILENO);
            dup2(errorFD, STDERR_FILENO);

            if (execvp(args[0], args) < 0) {
                fprintf(stderr, "Command %s failed to execute.\n", args[0]);
                exit(2);
            }

        } else {
            fprintf(stdout, "Starting command %d: child PID %d of parent PPID %d\n", commandCount, p, getpid());
            fflush(stdout);
            i++;
        }
        close(outputFD);
        close(errorFD);
    }

    while (i > 0) {
        pid_t pid = wait(&status);

        if (WIFEXITED(status)) {
            fprintf(stdout, "Finished child PID %d of parent PPID %d\n", p, getpid());
            fflush(stdout);
        } else if (WIFSIGNALED(status)) {
            fprintf(stderr, "Child process %d terminated by signal %d\n", p, WTERMSIG(status));
            fflush(stderr);
        }

        snprintf(outputFile, sizeof(outputFile), "%d.out", p);
        snprintf(errorFile, sizeof(errorFile), "%d.err", p);

        int exit_code = WEXITSTATUS(status);

        if (exit_code != 0) {
            fprintf(stderr, "Command %s exited with exitcode = %d\n", args[0], exit_code);
            fflush(stderr);
        }

        i--;
    }

    return 0;
}
