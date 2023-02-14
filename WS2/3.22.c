/**
 * Description: This module takes three numbers from the user. It then compares the three numbers given and prints out the smallest integer.
 * Author names: Mark Ibarra
 * Author emails: mark.ibarra@sjsu.edu
 * Last modified date: 2/13/2023
 * Creation date: 2/13/2023
 **/

#include <stdio.h>

int main(void) {

   int num1;
   int num2;
   int num3;

   scanf("%d %d %d", &num1, &num2, &num3);
   int smallest = num1;

   if (smallest  > num2)
      smallest = num2;
   if (smallest > num3)
      smallest = num3;

   printf("%d\n", smallest);

   return 0;
}

