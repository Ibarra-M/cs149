/**
 * Description: This module takes an integer and converts it into reverse binary.
 * Author names: Mark Ibarra
 * Author emails: mark.ibarra@sjsu.edu
 * Last modified date: 2/20/2023
 * Creation date: 2/20/2023
 **/
 
#include <stdio.h>

int main(void){

    int num;

    printf("Enter a number:");
    scanf("%d", &num); //places given integer into num int

    printf("Reverse binary code for %d is: ", num);//prints given integer
    while (num > 0){ //while loop to perform mod division and prints 0s and 1s
        printf("%d", num % 2);
        num = num/2;
    }
    printf("\n");

    return 0;
}
