/**
 * Description: This module reverse prints the given integers.
 * Author names: Mark Ibarra
 * Author emails: mark.ibarra@sjsu.edu
 * Last modified date: 2/20/2023
 * Creation date: 2/20/2023
 **/

#include <stdio.h>

int main(void) {
    const int NUM_ELEMENTS = 20;
    int userVals[NUM_ELEMENTS];
    int count = 0;
    int numbers;
    int size;

    //takes user's array sizet
    printf("Enter size array(20 MAX):");
    scanf("%d", &size);

    //while loop stops when size equals to 0
    while(size != 0){
        scanf("%d", &numbers);
        //adds user's integer into next element in array
        userVals[count] = numbers;
        count++;
        size--;
   }
    //for loop that pulls out integers from array
    for(int i = count-1; i >= 0; i--){
        printf("%d,", userVals[i]);
    }
    printf("\n");

   return 0;
}
