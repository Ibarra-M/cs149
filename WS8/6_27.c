/**
 * Description: This module takes a user input character and a string. Once the charcter and string is read, it counts
 * the occurrences of the character within the string given.
 * Author names: Mark Ibarra
 * Author emails: mark.ibarra@sjsu.edu
 * Last modified date: 4/3/2023
 * Creation date: 4/3/2023
 **/

#include <stdio.h>
#include <string.h>

int CalcNumCharacters(char* userString, char userChar){

    int occurrence = 0;
    size_t size = strlen(userString);
    for(int i = 0; i < size; i++){
        if(userString[i] == userChar){
            occurrence++;
        }else{
            continue;
        }
    }
    return occurrence;
}

int main(void) {
    char userString[50];
    char userChar;

    printf("Enter a charcter followed by a string:");
    scanf("%c %s", &userChar, userString);

    printf("Results:\n");
    if((CalcNumCharacters(userString, userChar) == 0) || (CalcNumCharacters(userString, userChar) > 1)){
        printf("%d %c's\n", CalcNumCharacters(userString, userChar), userChar);
    }
    else{
        printf("%d %c\n", CalcNumCharacters(userString, userChar), userChar);
    }
    return 0;
}
