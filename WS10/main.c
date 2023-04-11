/**
 * Description: This module uses three files
 * Author names: Mark Ibarra
 * Author emails: mark.ibarra@sjsu.edu
 * Last modified date: 4/3/2023
 * Creation date: 4/3/2023
 **/
#include <stdio.h>
#include <string.h>

#include "ItemToPurchase.h"

 int main() {
    ItemToPurchase item1;
    ItemToPurchase item2;

    char c;

    MakeItemBlank(&item1);
    MakeItemBlank(&item2);

    printf("Item 1\n");
    printf("Enter the item name:\n");
    fgets(item1.itemName, sizeof(item1.itemName), stdin);
    item1.itemName[strcspn(item1.itemName, "\n")] = 0;
    printf("Enter the item price:\n");
    scanf("%lf", &item1.itemPrice);
    printf("Enter the item quantity:\n");
    scanf("%d", &item1.itemQuantity);

    c= getchar();
    while(c != '\n' && c != EOF) {
        c = getchar();
    }

    printf("\n");
    printf("Item 2\n");
    printf("Enter the item name:\n");
    fgets(item2.itemName, sizeof(item2.itemName), stdin);
    item2.itemName[strcspn(item2.itemName, "\n")] = 0;
    printf("Enter the item price:\n");
    scanf("%lf", &item2.itemPrice);
    printf("Enter the item quantity:\n");
    scanf("%d", &item2.itemQuantity);

    PrintItemCost(item1, item2);

    return 0;
}
