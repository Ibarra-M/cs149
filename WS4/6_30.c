/**
 * Description: This module uses two functions outside main to discover the maximum and minimum in a given array of size 4.
 * Author names: Mark Ibarra
 * Author emails: mark.ibarra@sjsu.edu
 * Last modified date: 2/27/2023
 * Creation date: 2/27/2023
 **/

#include <stdio.h>

//function that discovers the maximum in a given array of size 4
int MaxNumber(int num1, int num2, int num3, int num4){

    int numbers[] = {num1, num2, num3, num4};     //places the numbers read into an array
    int maximum = numbers[0];   //sets the first number in array to be maximum
    size_t size = sizeof(numbers) / sizeof(numbers[0]); //counts the elements in array

    //for loop to compare numbers to the array and set the biggest number into maximum
    for(int i = 0; i < size; i++){
        if(maximum < numbers[i])
            maximum = numbers[i];
    }
    //returns the maximum read from the array
    return maximum;
}
//function that discovers the minimum in a given array of size 4
int MinNumber(int num1, int num2, int num3, int num4){

    int numbers[] = {num1, num2, num3, num4};   //places the numbers read into an array
    int minimum = numbers[0];   ////sets the first number in array to be minimum
    size_t size = sizeof(numbers) / sizeof(numbers[0]); //counts the elements in array

    //for loop to compare numbers to the array and set the smallest number into minimum
    for(int i = 0; i < size; i++){
        if(minimum > numbers[i])
            minimum = numbers[i];
    }
    //returns the minimum read from array
    return minimum;
}

int main(void) {

    int num1, num2, num3, num4;

    printf("Enter four numbers to find the Maximum and Minimum: \n");
    scanf("%d %d %d %d", &num1, &num2, &num3, &num4);

    //send the read numbers in the functions outside of main to find the maximum and minimum
    printf("Maximum is %d\n", MaxNumber(num1, num2, num3, num4));
    printf("Minimum is %d\n", MinNumber(num1, num2, num3, num4));

   return 0;
}
