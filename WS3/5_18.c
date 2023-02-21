/**
 * Description: This module takes integers and and places them into an array. The program then runs through the array and compares them to the last element. If the comparing number is less than the last element in the array, the program will print the value.
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
    int lastInt;
    int size;

    //ask user to enter array size any array over 20 will be ignored.
    printf("Enter size array(20 MAX):");
    scanf("%d", &size);

    //saves the last integer of the array for comparing
    lastInt = size;

    //while loop to take integers and place them into an array
    while(count <= size){
        scanf("%d", &numbers);
        userVals[count] = numbers;
        count++;
        //size--;
    }
    //for loop to go through the array one by one
    for(int i = 0; i < count-1; i++){
        //compares each element to the last element
        if(userVals[i] <= userVals[lastInt]){
            printf("%d,", userVals[i]);
        };
    }
    printf("\n");
    return 0;
}
