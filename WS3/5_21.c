/**
 * Description: This module reads each given word and prints out the words with the character asked to find in each word.
 * Author names: Mark Ibarra
 * Author emails: mark.ibarra@sjsu.edu
 * Last modified date: 2/20/2023
 * Creation date: 2/20/2023
 **/

#include <stdio.h>

int main(void) {
    char words[20][10];
    int size;
    char searchCharacter;

    //User array size the input values
    scanf("%d", &size);

    //Adds the given words into an array. Each word in its own element space
    for (int i = 0; i < size; i++) {
        scanf("%s", words[i]);
    }

    //the character to find in each word
    scanf(" %c", &searchCharacter);

    //for loop that find words that contain the searchCharacter
    for (int i = 0; i < size; i++) {
        for (int j = 0; words[i][j] != '\0'; j++) {
            if (words[i][j] == searchCharacter) {
                printf("%s,", words[i]);
                break;
            }
        }
    }
  printf("\n");

   return 0;
}
