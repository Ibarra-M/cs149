/**
 * Description: This module takes integers and inserts them into an array. The program then finds the middle value.
 * Author names: Mark Ibarra
 * Author emails: mark.ibarra@sjsu.edu
 * Last modified date: 2/20/2023
 * Creation date: 2/20/2023
 **/

#include <stdio.h>

int main(void) {
    const int NUM_ELEMENTS = 9;
    int userVals[NUM_ELEMENTS];
    int count = 0;
    int numbers;
    int middle;

    //while loop that takes user input.
    while(numbers >= 0){
        scanf("%d", &numbers);
        userVals[count] = numbers;
        //if statement watches if -1 has been entered
        if (numbers < 0){
            break;
        }
        count++;
    }
    //finds middle value in the array
    middle = userVals[count/2];
    //prints error if array is larger than 9
    if (count > 9){
        printf("Too many numbers\n");
    }
    else{
        printf("Middle item: %d\n", middle);
    }
    return 0;
}
