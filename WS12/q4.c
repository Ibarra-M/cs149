/**
 * Description: This module is a simple program that allocates
 * memory using malloc(). Main reason for this module is to test out memory leaks
 * In q4, running ./main in terminal (when memory has not been freed), nothing happens. When
 * Valgrind --leak-check=full ./main is runned, it gives a "error summary: 1 errors from 1
 * contexts.' Valgrind states that there is a block that are definitely lost in record 1 of 1.
 * Author names: Mark Ibarra
 * Author emails: mark.ibarra@sjsu.edu
 * Last modified date: 4/24/2023
 * Creation date: 4/24/2023
 **/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void) {
    int *test;

    if((test = malloc(sizeof(int) * 1)) == NULL){
        printf("UNABLE TO ALLOCATE MEMORY!");
        return -1;
    }

    free(test); //comment out to test out memory leak (using valgrind)

    return 0;
}
