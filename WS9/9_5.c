/**
 * Description: This module takes a user string and parses the string into two separate strings of their own.
 * It has a constraint that a comma must be entered to separate the words from the initial input.
 * Author names: Mark Ibarra
 * Author emails: mark.ibarra@sjsu.edu
 * Last modified date: 4/3/2023
 * Creation date: 4/3/2023
 **/

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int main(void) {
    char userInput[100];
    char firstStr[50];
    char secondStr[50];
    int inputValues;
    bool inputDone = false;

    while(!inputDone){

        printf("Enter input string: \n");
        fgets(userInput, 100, stdin);

        // inputValues reads how many words have been entered. it also parses userInput into firstStr & secondStr.
        inputValues = sscanf(userInput, "%49[^,], %49s", firstStr, secondStr);

        firstStr[strcspn(firstStr, "\n")] = 0;
        // detects q and kills the while loop.
        if (strcmp(firstStr, "q") == 0) {
            inputDone = true; //Sets boolean to true when q is entered. Ends while loop
            return 0;
        }
        // if a comma is found and two values are inputed, the program prints the parsed words.
        if ((strchr(userInput, ',') != NULL) && (inputValues == 2)){
            printf("First word: %s\n", firstStr);
            printf("Second word: %s\n\n", secondStr);
        }
        // error message
        else {
            printf("Error: No comma in string.\n\n");
        }
    }
    return 0;
}
