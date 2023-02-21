/**
 * Description: This module reads a given array and a given bound to print numbers in the array within the given range.
 * Author names: Mark Ibarra
 * Author emails: mark.ibarra@sjsu.edu
 * Last modified date: 2/20/2023
 * Creation date: 2/20/2023
 **/

#include <stdio.h>

int main(void) {

    int size;
    int lowerBound;
    int upperBound;

    //Asks user to enter the size of the array
    printf("Enter the size of the array: ");
    scanf("%d", &size);

    //makes array the size user desired
    int numbers[size];

    //reads user's numbers to enter into array
    for(int i = 0; i < size; i++){
        scanf("%d", &numbers[i]);
    }

    printf("Enter the upper and lower bound: ");
    //takes the lower and upper bound
    scanf("%d %d", &lowerBound, &upperBound);

	for(int i = 0; i < size; i++) {
            if (numbers[i] >= lowerBound && numbers[i] <= upperBound){

                printf("%d,", numbers[i]);
            }
    }

    printf("\n");

    return 0;
}
