/**
 * Description: This module divides a given integer three times and prints each result
 * Author names: Mark Ibarra
 * Author emails: mark.ibarra@sjsu.edu
 * Last modified date: 2/13/2023
 * Creation date: 2/13/2023
 **/
 
#include <stdio.h>

int main(void){

    int userNum;
    int divideBy;

    scanf("%d %d", &userNum, &divideBy);
    printf("%d %d %d\n", (userNum/divideBy), ((userNum/divideBy)/divideBy), (((userNum/divideBy)/divideBy)/divideBy) );

    return 0;
}
