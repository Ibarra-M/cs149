/**
 * Description: This module converts a users lap count to miles. A function outside of main is used.
 * Author names: Mark Ibarra
 * Author emails: mark.ibarra@sjsu.edu
 * Last modified date: 2/27/2023
 * Creation date: 2/27/2023
 **/

#include <stdio.h>
//funtion that reads user input and multiplies it by .25
double LapsToMiles(double userLaps){
   return (.25 * userLaps);
}
int main(void) {
   
   double userLaps;

   printf("Enter laps completed:  ");
   scanf("%lf", &userLaps);
   
   /**printf funtion that send the given number from user into the funtion outside of
    * main to calculate the miles.
    **/
   printf("You ran %0.2f laps which is %0.2lf miles.\n",userLaps, LapsToMiles(userLaps));
   
   return 0;
}
