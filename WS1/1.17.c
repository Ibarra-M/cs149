/**
 * Description: This module Uses print statements to print out an arrow sing any two digits entered.
 * Author names: Mark Ibarra
 * Author emails: mark.ibarra@sjsu.edu
 * Last modified date: 2/6/2023
 * Creation date: 2/6/2023
 **/
 
#include <stdio.h>

int main(void){
    int baseInt;
    int headInt;
    
    printf("Enter two digits: ");
    scanf("%d %d", &baseInt , &headInt);
    
    printf("    %d\n", headInt);
    printf("    %d%d\n", headInt , headInt);
    printf("%d%d%d%d%d%d%d\n", baseInt, baseInt, baseInt, baseInt, headInt , headInt, headInt);
    printf("%d%d%d%d%d%d%d%d\n", baseInt, baseInt, baseInt, baseInt,headInt , headInt, headInt , headInt);
    printf("%d%d%d%d%d%d%d\n", baseInt, baseInt, baseInt, baseInt,headInt , headInt, headInt);
    printf("    %d%d\n", headInt , headInt);
    printf("    %d\n", headInt);
    return 0;
}
