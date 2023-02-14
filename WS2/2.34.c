/**
 * Description: This module demonstrates how to take a string input and print it out through printf.
 * Author names: Mark Ibarra
 * Author emails: mark.ibarra@sjsu.edu
 * Last modified date: 2/13/2023
 * Creation date: 2/13/2023
 **/

 #include <stdio.h>

int main(void) {

   char userName[50];

   scanf("%s", userName);
   printf("Hello %s, and welcome to CS Online!\n", userName);

   return 0;
}
