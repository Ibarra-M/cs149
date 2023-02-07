/**
 * Description: This module takes in a user input and uses print statements to perform simple math fuctions within the print itself.
 * Author names: Mark Ibarra
 * Author emails: mark.ibarra@sjsu.edu
 * Last modified date: 2/6/2023
 * Creation date: 2/6/2023
 **/

#include <stdio.h>

int main(void) {
   int userNum;
   int userNum2;
   
   printf("Enter integer:\n");
   scanf("%d", &userNum);
   
   printf("You entered: %d\n", userNum);
   printf("%d squared is %d\n", userNum, userNum*userNum);
   printf("And %d cubed is %d!!\n", userNum, userNum*userNum*userNum);
   
   printf("Enter another integer:\n");
   scanf("%d", &userNum2);
   
   printf("%d + %d is %d\n", userNum, userNum2, userNum+userNum2);
   printf("%d * %d is %d\n", userNum, userNum2, userNum*userNum2);

   return 0;
}
