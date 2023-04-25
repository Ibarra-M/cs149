/**
 * Description: This module is a simple program that sets an integer of size malloc 100
 * to zero. Zero is passed into each data array iterating through one by one, 100 times.
 * In q6, the program runs ./main in terminal and prints a random number. When the program is runned
 * in termainal using valgrind, all heaps were freed, but 1 error from 1 context occurs.
 * Author names: Mark Ibarra
 * Author emails: mark.ibarra@sjsu.edu
 * Last modified date: 4/24/2023
 * Creation date: 4/24/2023
 **/

#include <stdio.h>
#include <stdlib.h>

int main() {
    int i;
    int *data = (int*)malloc(sizeof(int) * 100);

    for(i = 0; i < 100; i++) {
        data[i] = 0;
    }

    free(data);

    printf("Data freed = %d\n", *data);

    return 0;

}
