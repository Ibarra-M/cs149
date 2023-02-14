/**
 * Description: This module takes three floating point numbers and displayes them with two decimal points while performing simpla math functions.
 * Author names: Mark Ibarra
 * Author emails: mark.ibarra@sjsu.edu
 * Last modified date: 2/13/2023
 * Creation date: 2/13/2023
 **/
#include <stdio.h>
#include <math.h>

int main(void) {
   double x;
   double y;
   double z;

   scanf("%lf %lf %lf", &x, &y, &z);
   printf("%0.2f %0.2f %0.2f %0.2f \n", pow(x,z), pow(x,pow(y,2)), fabs(y), sqrt(pow(x*y,z)));

   return 0;
}

