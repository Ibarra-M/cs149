/**
 * Description: This module takes a string with 50 being the maximum length, and it reverse prints the netered string.
 * Author names: Mark Ibarra
 * Author emails: mark.ibarra@sjsu.edu
 * Last modified date: 3/13/2023
 * Creation date: 3/13/2023
 **/

#include <stdio.h>
#include <string.h>

int main(void) {
    int maxLength = 50;
    char userString[maxLength];

    while (1) {

        printf("Enter a string to reverse it (exit, type done, Done, or d): ");
        // Read users input
        fgets(userString, maxLength, stdin);

        // Checks if user has entered any version of done to exit program
        if ((strcmp(userString, "Done\n") == 0) || (strcmp(userString, "done\n") == 0) || (strcmp(userString, "d\n") == 0)) {
            printf("Program ended\n");
            break;
        }
        else{
            int length = strlen(userString);
            for (int i = 0; i < length / 2; i++) {
                char temp = userString[i];
                userString[i] = userString[length - i - 2];
                userString[length - i - 2] = temp;
            }
        }
        printf("Reverse String: ");
        printf("%s", userString);
    }
    return 0;
}
