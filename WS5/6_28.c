/**
 * Description: This module takes a user string with special characters and prints only the letters with not spaces
 * Author names: Mark Ibarra
 * Author emails: mark.ibarra@sjsu.edu
 * Last modified date: 3/6/2023
 * Creation date: 3/6/2023
 **/

#include <stdio.h>
#include <string.h>

void RemoveNonAlpha(char userString[], char userStringAlphaOnly[]){

    int i;
    int j;

     //This for loop reads the entered array from main.
    for(i = 0; userString[i] != '\0'; i++){
        /**
         * A conditional while loop breaks when a letter is found so it can assign it to userStringAlphaOnly.
         * When a special character is found, the while loop sends it to the nested for loop. The nested for loop
         * within the while loop removes the found special character by shifting the array by one.
         **/

        while ( ! ((userString[i] >= 'A' && userString[i] <= 'Z') || (userString[i] >= 'a' && userString[i] <= 'z') || userString[i] == '\0')){
            for(j = i; userString[j] != '\0'; j++){
                userString[j] = userString[j+1];
            }
            //Makes the last character a null. This is done to shorten the array after the shift.
            userString[j] = '\0';
        }
        //when while loop finds a letter in userString, it jumps here and passes the character to userStringAlphaOnly.
        userStringAlphaOnly[i] = userString[i];
    }
}



int main(void) {

    int size = 50;
    char userString[size];
    char userStringAlphaOnly[size];

    //ask user to enter a string.
    printf("Enter a string of maximum length 50: ");
    fgets(userString, size, stdin);

    //sends the read array to RemoveNonAlpha function
    RemoveNonAlpha(userString,userStringAlphaOnly);

    //prints the new array from the RemoveNonAlpha function
    printf("\nOnly letters of your string is: %s\n", userStringAlphaOnly);
    return 0;
}
