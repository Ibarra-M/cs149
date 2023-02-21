/**
 * Description: This module takes multiple integers, one by one, and prints out the max and average.
 * Author names: Mark Ibarra
 * Author emails: mark.ibarra@sjsu.edu
 * Last modified date: 2/20/2023
 * Creation date: 2/20/2023
 **/

#include <stdio.h>

int main(void) {
   int total = 0;
   int numbers = 0;
   int count = -1;
   int max = 0;;
   double average;

   printf("Enter any positive numbers (-1 to exit): \n");
   //while loop which makes any number below 0 to stop the loop
   while(numbers >= 0){
      count++;
      total = total + numbers;
      //finds max every loop
      if (max  < numbers)
         max = numbers;
      //takes user input
      scanf("%d", &numbers);

   }
   //calculates average with double format
   average = (double)total/count;

   printf("%d %0.2lf\n", max, average);
   return 0;
}
