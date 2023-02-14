/**
 * Description: This module takes performs simple math calculations using float and integers. Format of float is adjusted to match zyBooks.
 * Author names: Mark Ibarra
 * Author emails: mark.ibarra@sjsu.edu
 * Last modified date: 2/13/2023
 * Creation date: 2/13/2023
 **/

 #include <stdio.h>

int main(void) {
   int currentPrice;
   int lastMonthsPrice;

   scanf("%d", &currentPrice);
   scanf("%d", &lastMonthsPrice);

   printf("This house is $%d. The change is $%d since last month.\n", currentPrice, currentPrice-lastMonthsPrice);
   printf("The estimated monthly mortgage is $%f.\n", (currentPrice*0.051)/12);

   return 0;
}
