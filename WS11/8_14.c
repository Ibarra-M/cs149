/**
 * Description: This module asks user to enter three names and their phone numbers ro print them out. The module uses
 * a linked list data structure to initialize the data bein read from the user.
 * Author names: Mark Ibarra
 * Author emails: mark.ibarra@sjsu.edu
 * Last modified date: 4/17/2023
 * Creation date: 4/17/2023
 **/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//the structure of a single node in a linked list. Nodes contain the name and phone number and the next node in the list
typedef struct ContactNode_struct {
    char contactName[30];
    char contactPhoneNumber[15];
    struct ContactNode_struct* nextNodePtr;
} ContactNode;

//function initializes the created ContactNode
void InitializeContactNode(ContactNode* thisNode, char name[], char phone[]){
    strcpy(thisNode->contactName, name);
    strcpy(thisNode->contactPhoneNumber, phone);
    thisNode->nextNodePtr = NULL;
}

//function to pull name from linked list
void* GetName(ContactNode* thisNode){
    return thisNode->contactName;
}

//function to pull phoneNumber from linked list
void* GetPhoneNumber(ContactNode* thisNode){
    return thisNode->contactPhoneNumber;
}

//InsertAfter is a funtion that inserts a new ContactNode after a given ContactNode in a linked list
void InsertAfter(ContactNode* thisNode, ContactNode* newNode){
    ContactNode* tempNextNode = thisNode->nextNodePtr;
    thisNode -> nextNodePtr = newNode;
    newNode -> nextNodePtr = tempNextNode;
}

//function to get access of the next node pointer
void* GetNext(ContactNode* thisNode){
    return thisNode->nextNodePtr;
}

//Print function to print information from the linked list
void PrintContactNode(ContactNode* thisNode){
    printf("Name: %s\nPhone number: %s\n",thisNode->contactName, thisNode->contactPhoneNumber);
}

int main(void) {
    char name[30];
    char phoneNumber[15];
    int i;

    ContactNode* topNode = NULL;
    ContactNode* currentNode = NULL;
    ContactNode* nextNode = NULL;

    printf("Enter a full name follwed by their number (three total contacts):\n");
    fgets(name, sizeof(name), stdin);
    fgets(phoneNumber, sizeof(phoneNumber), stdin);

    name[strcspn(name, "\n")] = '\0';
    phoneNumber[strcspn(phoneNumber, "\n")] = '\0';

    //dynamically allocate memory size and assign pointer of the to topNode
    topNode = malloc(sizeof(ContactNode));
    //initialize withthe first user input name and phonenumber
    InitializeContactNode(topNode, name, phoneNumber);
    //currentNode set to point to the first node
    currentNode = topNode;

    //for loop to receive the second and third user input and add them to the linked list
    for(i = 2; i <= 3; i++){
        fgets(name, sizeof(name), stdin);
        fgets(phoneNumber, sizeof(phoneNumber), stdin);

        name[strcspn(name, "\n")] = '\0'; //remove newline
        phoneNumber[strcspn(phoneNumber, "\n")] = '\0';

        nextNode = malloc(sizeof(ContactNode));
        InitializeContactNode(nextNode, name, phoneNumber);
        InsertAfter(currentNode, nextNode);
        currentNode = nextNode;
    }

    printf("\n");
    currentNode = topNode;
    for (int i = 1; currentNode != NULL; i++) {
        printf("Person %d: %s, %s\n", i, (char*) GetName(currentNode), (char*) GetPhoneNumber(currentNode));
        currentNode = GetNext(currentNode);
    }

    //Print out the linked list
    printf("\nContact List\n");
    currentNode = topNode;
    while (currentNode != NULL) { //while loop to iterate through linked list
        PrintContactNode(currentNode);
        printf("\n");
        currentNode = GetNext(currentNode);
    }

    //free memory allocated to the linked list
    currentNode = topNode;
    while (currentNode != NULL) {
        nextNode = currentNode->nextNodePtr;
        free(currentNode);
        currentNode = nextNode;
    }

    return 0;
}
