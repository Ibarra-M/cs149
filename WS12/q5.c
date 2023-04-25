/**
 * Description: This module is a simple program that sets an integer of size malloc 100
 * to zero. In q5, When the compiled version is runned, nothing happens. When the program is run
 * using algrind, we get a invalid write of size 4. These memory leaks occur due to data[100] not
 * being allocated properly.
 * Author names: Mark Ibarra
 * Author emails: mark.ibarra@sjsu.edu
 * Last modified date: 4/24/2023
 * Creation date: 4/24/2023
 **/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void) {

    int *data = (int*)malloc(sizeof(int) * 100);
    data[100] = 0;

    return 0;
}
