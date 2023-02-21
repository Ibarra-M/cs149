/**
 * Description: This module pulls the two smallest integers of a given array.
 * Author names: Mark Ibarra
 * Author emails: mark.ibarra@sjsu.edu
 * Last modified date: 2/20/2023
 * Creation date: 2/20/2023
 **/

#include <stdio.h>

int main(void) {
    int size;
    int smallest1;
    int smallest2;

    //Asks user to enter the size of the array
    printf("Enter the size of the array: ");
    scanf("%d", &size);

    //makes array the size user desired
    int numbers[size];

    //reads user's numbers to enter into array
    for(int i = 0; i < size; i++){
        scanf("%d", &numbers[i]);
    }
    //initialzes smallest1 and smallest2 with the first indexes of the array
    smallest1 = numbers[0];
    smallest2 = numbers[1];

    //swaps smallest1 and smallest2 if necessary
    if(smallest2 < smallest1){
        int temp = smallest1;
        smallest1 = smallest2;
        smallest2 = temp;
    }

    //for loop to loop through the remaining numbers to compare
	for(int i = 2; i < size; i++) {
            if (numbers[i] < smallest1) {
                smallest2 = smallest1;
                smallest1 = numbers[i];
            }else if(numbers[i] < smallest2){
                smallest2 = numbers[i];
            }

	}

    printf("%d and %d\n", smallest1, smallest2);

    return 0;
}
