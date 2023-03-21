/**
 * Description: This module uses a SwapValues functions to swap the balues referenced by parameters.
 * Author names: Mark Ibarra
 * Author emails: mark.ibarra@sjsu.edu
 * Last modified date: 3/20/2023
 * Creation date: 3/20/2023
 **/

#include <stdio.h>
#include <string.h>

//SwapValues function that reads the values pointers and swaps
void SwapValues(int* userVal1, int* userVal2, int* userVal3, int* userVal4){
    int temp = *userVal1;
    *userVal1 = *userVal2;
    *userVal2 = temp;

    temp = *userVal3;
    *userVal3 = *userVal4;
    *userVal4 = temp;

}

int main(void) {
    //creates variables
    int userVal1, userVal2, userVal3, userVal4;

    //recevies the input from user
    scanf("%d %d %d %d",&userVal1,&userVal2,&userVal3,&userVal4);

    //sends the pointer value to the function
    SwapValues(&userVal1,&userVal2,&userVal3,&userVal4);

    //prints the swapped values
    printf("%d %d %d %d\n", userVal1,userVal2,userVal3,userVal4);


    return 0;
}
