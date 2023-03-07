/**
 * Description: This module takes a user input and counts the letters and numbers only.
 * Author names: Mark Ibarra
 * Author emails: mark.ibarra@sjsu.edu
 * Last modified date: 3/6/2023
 * Creation date: 3/6/2023
 **/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main(void) {
    //initializes p to hold PID
    pid_t p;

    for(int i = 0; i < 4; i++){
      //sets p to contain child process and sets a new on each loop.
      p = fork();
      //safety net incase fork fails
      if(p < 0){
        fprintf(stderr, "fork failed\n");
        return 1;
      }
      //prints current proces ID from the given array.
      else if (p == 0){
        printf("hello world from PID %d!\n", getpid());
        //returns 0 to allow only the currrent process to be printed
        return 0;
      }
    }
}

