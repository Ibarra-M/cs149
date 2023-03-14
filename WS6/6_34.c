/**
 * Description: This module reads a list of user input integers, and runs it through booleans to find if they are
 * multiples of 10.
 * Author names: Mark Ibarra
 * Author emails: mark.ibarra@sjsu.edu
 * Last modified date: 3/13/2023
 * Creation date: 3/13/2023
 **/
#include <stdio.h>
#include <stdbool.h>

// Boolean that checks if all integers are multiples of 10
bool IsArrayMult10(int inputVals[], int numVals){
    for(int i = 0; i < numVals; i++){
        if((inputVals[i] %10) != 0){
            return false;
        }
    }
    return true;
}

// Boolean that checks if all integers are NOT multiples of 10
bool IsArrayNoMult10(int inputVals[], int numVals){
    for(int i = 0; i < numVals; i++){
        if((inputVals[i] %10) == 0){
            return false;
        }
    }
    return true;
}

int main(void) {
    int inputVals[20];
    int numVals = 0;

    printf("Enter the amount of numbers to enter: ");
    scanf("%d", &numVals);

    printf("Now enter %d different numbers: ", numVals);
    for(int i = 0; i < numVals; i++){
        scanf("%d", &inputVals[i]);
    }

    // Runs integers into functions to check if true of false
    if(IsArrayMult10(inputVals,numVals)){
        printf("all multiples of 10\n");
    }
    else if(IsArrayNoMult10(inputVals, numVals)){
        printf("no multiples of 10\n");
    }
    else {
        printf("mixed values\n"); //Prints if botg boolean functions are false
    }

   return 0;
}
