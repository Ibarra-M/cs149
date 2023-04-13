#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

#define MAX_ARGS 30
#define MAX_CMD_LEN 100

/**
 * CS149 assignment#4 helper code.
 * See the TODO's in the comments below! You need to implement those.
 * TRACE_NODE_STRUCT is a linked list of
 * pointers to function identifiers
 * TRACE_TOP is the head of the list is the top of the stack
**/

struct TRACE_NODE_STRUCT {
    char* functionid; // ptr to function identifier (a function name)
    struct TRACE_NODE_STRUCT* next; // ptr to next frama
};

typedef struct TRACE_NODE_STRUCT TRACE_NODE;
static TRACE_NODE* TRACE_TOP = NULL; // ptr to the top of the stack

/* --------------------------------*/
/* function PUSH_TRACE */
/*
* The purpose of this stack is to trace the sequence of function calls,
* just like the stack in your computer would do.
* The "global" string denotes the start of the function call trace.
* The char *p parameter is the name of the new function that is added to the call
trace.
* See the examples of calling PUSH_TRACE and POP_TRACE below
* in the main, make_extend_array, add_column functions.
**/

void PUSH_TRACE(char* p) // push p on the stack
{
    TRACE_NODE* tnode;
    static char glob[]="global";
    if (TRACE_TOP==NULL) {
        // initialize the stack with "global" identifier
        TRACE_TOP=(TRACE_NODE*) malloc(sizeof(TRACE_NODE));
        // no recovery needed if allocation failed, this is only
        // used in debugging, not in production
        if (TRACE_TOP==NULL) {
            printf("PUSH_TRACE: memory allocation error\n");
            exit(1);
        }
        TRACE_TOP->functionid = glob;
        TRACE_TOP->next=NULL;
    }//if

    // create the node for p
    tnode = (TRACE_NODE*) malloc(sizeof(TRACE_NODE));

    // no recovery needed if allocation failed, this is only
    // used in debugging, not in production
    if (tnode==NULL) {
        printf("PUSH_TRACE: memory allocation error\n");
        exit(1);
    }//if

    tnode->functionid=p;
    tnode->next = TRACE_TOP; // insert fnode as the first in the list
    TRACE_TOP=tnode; // point TRACE_TOP to the first node
}/*end PUSH_TRACE*/

/* --------------------------------*/
/* function POP_TRACE */
/* Pop a function call from the stack */

// remove the op of the stack
void POP_TRACE() {
    TRACE_NODE* tnode;
    tnode = TRACE_TOP;
    TRACE_TOP = tnode->next;
    free(tnode);
}/*end POP_TRACE*/


/* ---------------------------------------------- */
/* function PRINT_TRACE prints out the sequence of function calls that are on the
stack at this instance */
/* For example, it returns a string that looks like: global:funcA:funcB:funcC. */
/* Printing the function call sequence the other way around is also ok:
funcC:funcB:funcA:global */

char* PRINT_TRACE() {

    int depth = 50; //A max of 50 levels in the stack will be combined in a string for printing out.
    int i, length, j;
    TRACE_NODE* tnode;
    static char buf[100];

    if (TRACE_TOP==NULL) { // stack not initialized yet, so we are
        strcpy(buf,"global"); // still in the `global' area
        return buf;
    }

    /* peek at the depth(50) top entries on the stack, but do not
    go over 100 chars and do not go over the bottom of the
    stack */

    sprintf(buf,"%s",TRACE_TOP->functionid);
    length = strlen(buf); // length of the string so far

    for( i = 1, tnode = TRACE_TOP->next;
    tnode != NULL && i < depth;
    i++, tnode = tnode->next) {
        j = strlen(tnode->functionid); // length of what we want to add
        if (length+j+1 < 100) { // total length is ok
            sprintf(buf+length,":%s",tnode->functionid);
            length += j+1;
        }else // it would be too long
            break;
    }
    return buf;
} /*end PRINT_TRACE*/

// -----------------------------------------
// function REALLOC calls realloc
// TODO REALLOC should also print info about memory usage.
// TODO For this purpose, you need to add a few lines to this function.
// For instance, example of print out:
// "File mem_tracer.c, line X, function F reallocated the memory segment at address A to a new size S"
// Information about the function F should be printed by printing the stack (use PRINT_TRACE)
void* REALLOC(void* p,int t,char* file,int line) {
    PUSH_TRACE("REALLOC");

    int outputFile = open("memtrace.out", O_WRONLY | O_CREAT | O_APPEND, 0777);
    dup2(outputFile, 1);
    p = realloc(p,t);

    printf("File %s, line %d, function %s reallocated the memory segment at address %p to a new size %d\n", file, line, TRACE_TOP->functionid, p, t);
    printf("Information about the function %s. \nPrinting Stack: \n", TRACE_TOP->functionid);
    printf("%s\n", PRINT_TRACE());

    close(outputFile);

    POP_TRACE();

    return p;
}
// -------------------------------------------
// function MALLOC calls malloc
// TODO MALLOC should also print info about memory usage.
// TODO For this purpose, you need to add a few lines to this function.
// For instance, example of print out:
// "File mem_tracer.c, line X, function F allocated new memory segment at address A to size S"
// Information about the function F should be printed by printing the stack (use PRINT_TRACE)
void* MALLOC(int t,char* file,int line) {

    PUSH_TRACE("MALLOC");

    int outputFile = open("memtrace.out", O_WRONLY | O_CREAT | O_APPEND, 0777);
    dup2(outputFile, 1);
    void* p;
    p = malloc(t);

    printf("File %s, line %d, function %s reallocated the memory segment at address %p to a new size %d\n", file, line, TRACE_TOP->functionid,p,t);
    printf("Information about the function %s. \nPrinting Stack: \n", TRACE_TOP->functionid);
    printf("%s", PRINT_TRACE());

    close(outputFile);

    POP_TRACE();

    return p;
}
// ----------------------------------------------
// function FREE calls free
// TODO FREE should also print info about memory usage.
// TODO For this purpose, you need to add a few lines to this function.
// For instance, example of print out:
// "File mem_tracer.c, line X, function F deallocated the memory segment at address A"
// Information about the function F should be printed by printing the stack (use PRINT_TRACE)
void FREE(void* p,char* file,int line){

    PUSH_TRACE("FREE");

    int outputFile = open("memtrace.out", O_WRONLY | O_CREAT | O_APPEND, 0777);
    dup2(outputFile, 1);

    printf("File %s, line %d, function %s reallocated the memory segment at address %p\n", file, line, TRACE_TOP->functionid,p);
    printf("Information about the function %s. \nPrinting Stack: \n", TRACE_TOP->functionid);
    printf("%s", PRINT_TRACE());

    free(p);
    POP_TRACE();

}

#define realloc(a,b) REALLOC(a,b,__FILE__,__LINE__)
#define malloc(a) MALLOC(a,__FILE__,__LINE__)
#define free(a) FREE(a,__FILE__,__LINE__)

// -----------------------------------------
// function add_column will add an extra column to a 2d array of ints.
// This function is intended to demonstrate how memory usage tracing of realloc is done
// Returns the number of new columns (updated)
int add_column(int** array,int rows,int columns){
    PUSH_TRACE("add_column");
    int i;

    for(i=0; i<rows; i++) {
        array[i]=(int*) realloc(array[i],sizeof(int)*(columns+1));
        array[i][columns]=10*i+columns;
    }//for

    POP_TRACE();
    return (columns+1);
}// end add_column
// ------------------------------------------
// function make_extend_array
// Example of how the memory trace is done
// This function is intended to demonstrate how memory usage tracing of malloc and free is done

void make_extend_array() {

    PUSH_TRACE("make_extend_array");
    int i, j;
    int **array;
    int ROW = 4;
    int COL = 3;

    //make array
    array = (int**) malloc(sizeof(int*)*4); // 4 rows
    for(i=0; i<ROW; i++) {
        array[i]=(int*) malloc(sizeof(int)*3); // 3 columns
            for(j=0; j<COL; j++)
                array[i][j]=10*i+j;
    }//for

    //display array
    for(i=0; i<ROW; i++){
        for(j=0; j<COL; j++)
            printf("array[%d][%d]=%d\n",i,j,array[i][j]);
    }

    // and a new column
    int NEWCOL = add_column(array,ROW,COL);

    // now display the array again
    for(i=0; i<ROW; i++){
        for(j=0; j<NEWCOL; j++)
            printf("array[%d][%d]=%d\n",i,j,array[i][j]);
    }
    //now deallocate it
    for(i=0; i<ROW; i++){
        free((void*)array[i]);
    }
    free((void*)array);

    POP_TRACE();
    return;
}//end make_extend_array

// Variables for linked list data structure
struct CommandNode {
    char *command;
    int i;
    struct CommandNode *next;
};

// Function to create new nodes
void CreateCommandNode(struct CommandNode* newNode, char cmd[30], int index, struct CommandNode *nextCommand) {

    PUSH_TRACE("CreateCommandNode");
    newNode->command = (char*) malloc (sizeof(char) * 30);
    strcpy(newNode->command, cmd);
    newNode->i = index;
    newNode->next = nextCommand;

    POP_TRACE();
    
    return;
}

// Print funtion that prints all commands to a file
void PrintList(struct CommandNode *start) {
    if(start == NULL) {
        printf("Link list empty");
        return;
    }
    
    int outputFile = open("memtrace.out", O_WRONLY | O_CREAT | O_APPEND, 0777);
    dup2(outputFile, 1);

    printf("Command #%d = %s\n", start->i, start->command);
    PrintList(start->next);
    
    close(outputFile);
}

int main(int argc, char *argv[]) {
    
    char userCommands[MAX_CMD_LEN];
    char **dArray; //dynamic allocated array
    int lineCount = 0;
    int i;
    int rows = 10; // 10 lines to allow space in memory
    int columns = 30;


    PUSH_TRACE("main");

    FILE * memtraceFile = fopen(argv[1], "rw");
    if (memtraceFile == NULL){
        printf("Error: unable to open file\n");
        exit(1);
    }
    
    // Creates a char** in order to copy text
    dArray = (char**) malloc(sizeof(char*) * rows);
    for(i = 0; i < rows; i++) {
        dArray[i] = (char*) malloc(sizeof(char) * columns);
    }

    // reads and stores lines of text into the char**
    while (fgets(userCommands, sizeof(userCommands), memtraceFile)) {
        if (lineCount >= rows) {
            dArray = (char**) realloc(dArray, sizeof(char*) * (rows + 1));
            dArray[rows] = (char*) malloc(sizeof(char) * columns);
            rows += 1;
        }
        strcpy(dArray[lineCount], userCommands);
        lineCount++;
        memset(userCommands, 0, 20);
    }
    fclose(memtraceFile);
    
    // Prints directly from dynamic allocated array
    printf("\nPrinting from Array: \n");
    for (i = 0; i < lineCount; i++){
        printf("array[%d] = %s", i, dArray[i]);
    }

    // initialization CommandNode (linked list) structure from data dArray to store the lines of text
    // stores first element of te array
    struct CommandNode *commandList = (struct CommandNode*)malloc(sizeof(struct CommandNode));
    CreateCommandNode(commandList, dArray[0], 1, NULL);
    struct CommandNode *current = commandList; //current pointer to keep track of current node while iterating through array
    // interating through the rest of the elements of the array. 
    for(i = 1; i < lineCount; i++) {
        struct CommandNode *nextCommand = (struct CommandNode*)malloc(sizeof(struct CommandNode));
        CreateCommandNode(nextCommand, dArray[i], i+1, NULL);
        current->next = nextCommand;
        current = nextCommand;
    }
    
    // Printnode function called to print the text in the linked list
    printf("\nPrinting from Linked List: \n");
    PrintList(commandList);

    // whileloop to deallocate the linked list
    struct CommandNode *clear = commandList;
    while(commandList != NULL) {
            commandList = commandList->next;
            free(clear);
            clear = commandList;
        }
    
    // for loop to deallocate char**
    for(i = 0; i < lineCount; i++) {
        free((void*)dArray[i]);
    }
    free(dArray);
        
    POP_TRACE();
    return(0);

}
