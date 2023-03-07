/**
 * Description: This module takes a user string with special characters and prints only the letters with not spaces
 * Author names: Mark Ibarra
 * Author emails: mark.ibarra@sjsu.edu
 * Last modified date: 3/6/2023
 * Creation date: 3/6/2023
 **/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(int argc, char *argv[]) {

    char str[100];
    char names[100][30];
    char copyNames[100][30];
    int count = 0;
    int numberLines = 0;
    int occur[100] = {0};
    int duplicate;
    int fileCount = 1;
    int fd[2];
    pid_t p;

    /**
     * Reads text file give in command line

	FILE *fp = fopen(argv[1], "r");

    //If file does not exist or no txt file is named, this error will execute
    if (fp == NULL) {
        printf("cannot open file\n");
        return 1;
    }
    **/

    for (fileCount = 1; fileCount < argc; fileCount++){
        p = fork();

        if ( p < 0 ) {
			fprintf(stderr, "Fork failed");
			return 1;
		}

		else if ( p == 0 ) {
            close (fd[1]); // close reading end of first pipe.

            FILE *fp = fopen(argv[fileCount], "r");

            //If file does not exist or no txt file is named, this error will execute
            if (fp == NULL) {
                fprintf(stderr,"cannot open file\n");
                return 1;
            }
            /** This while loop reads lines from the given text file by using fgets function. This
             * begins writing content to stdout.
            **/
            while(fgets (str, 30, fp) != NULL) {

                //This line of code removes newline characters and replaces it with a null terminator.
                str[strcspn(str, "\n")] = '\0';

                /**If the length of a line read from the text file is zero, a warning print,
                * along with its numberLine will print
                *
                * */
                if (strlen(str) == 0) {
                    fprintf(stderr, "Warning - Line %d is empty.\n", ++numberLines);
                    continue;
                }
                //reads a string of length 30 from str and places it in names array
                if ( sscanf(str, "%30[^\n]", names[count]) == 1 ) {
                    count++;
                }
                //If any error outside of these limits occurs, this line will execute
                else {
                    printf("error reading line %d\n", numberLines);
                }
                //tracks lines being read
                numberLines++;
            }
            /**
            * This function closes the file that was being read from the command line. It is                * used to free up system resources
            **/
             fclose(fp);
             close(fd[1]);
        }
    }

    //this for loop clones the the names into another array
    for (int i = 0; i < count; i++) {
        strcpy(copyNames[i], names[i]);
    }

    /**
     * This for loop compares the two arrays and counts the occurrence for each name in
     * the array.
     **/
    for (int i = 0; i < count; i++) {
        for (int j = 0; j < count; j++) {
            if (strcmp(copyNames[i],names[j]) == 0) {
                occur[i]++;
            }
        }
    }
    /**
     * This for loop uses the logic to print only the names once along with their
     * occurences. This loop only uses the original names array.
     **/
    for(int i = 0; i < count;i++){
        duplicate = 0;
        for(int j = 0; j < i; j++){
            if (strcmp(names[i],names[j]) == 0){
                duplicate = 1;
                break;
            }
        }
        if(!duplicate){
            printf("%s: %d\n", names[i], occur[i]);
        }
    }

}
