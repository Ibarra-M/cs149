/**
 * Description: This module takes a user input and counts the letters and numbers only.
 * Author names: Mark Ibarra
 * Author emails: mark.ibarra@sjsu.edu
 * Last modified date: 3/6/2023
 * Creation date: 3/6/2023
 **/

#include <stdio.h>
#include <string.h>

int main(void) {

   int size = 50;
   int count = 0;
   char enterString[size];

   //request a string from user of lenth 50
   printf("Enter a string (less than 50 characters): ");
   fgets(enterString, size, stdin);

   /**
    * For loop checks each character found in the given array. If a special character is found, it'll ignore the
    * character and increment i. When a letter or number is found it'll increment count.
    **/
   for(int i =0; i < strlen(enterString); i++){
      if(enterString[i] != ' ' &&  enterString[i] != ',' && enterString[i] != '.' && enterString[i] != '!' && enterString[i] != '\n' && enterString[i] != '0' ){
         count++;
      }
   else{ continue; }
   }

   //prints the counted letters and numbers found in given array
   printf("letter and number count ony is %d\n", count);
   return 0;
}

