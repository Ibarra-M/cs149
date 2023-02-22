/*
 * Description: This module reads a given file and counts the names.
 * Author Name: Mark Ibarra
 * Author Email: mark.ibarra@sjsu.edu
 * Last modified date: 2/21/2023
 * Creation date: 2/21/2023
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {

    char str[100];
    char names[100][30];
    char copyNames[100][30];
    int count = 0;
    int numberLines = 0;
    int occur[100] = {0};
    int duplicate;

    /**
     * Reads text file give in command line
     * */
	FILE *fp = fopen(argv[1], "r");

    //If file does not exist or no txt file is named, this error will execute
    if (fp == NULL) {
        printf("cannot open file\n");
        return 1;
    }

    /**
     * This while loop reads lines from the given text file by using fgets function. this begins writing content to stdout.
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
    /**
     * This function closes the file that was being read from the command line. It is
     * used to free up system resources
     **/
    fclose(fp);

}
