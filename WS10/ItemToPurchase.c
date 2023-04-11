
#include <stdio.h>
#include <string.h>

#include "ItemToPurchase.h"


void MakeItemBlank(ItemToPurchase* itemTemp){

    strcpy(itemTemp->itemName,"none");
    itemTemp->itemPrice = 0;
    itemTemp->itemQuantity = 0;

}

void PrintItemCost(ItemToPurchase item1, ItemToPurchase item2){
    printf("\n");
    printf("TOTAL COST\n");
    printf("%s %d @ $%.2f = $%.2f\n", item1.itemName, item1.itemQuantity, item1.itemPrice, (item1.itemPrice*item1.itemQuantity));
    printf("%s %d @ $%.2f = $%.2f\n", item2.itemName, item2.itemQuantity, item2.itemPrice, (item2.itemPrice*item2.itemQuantity));
    printf("\n");
    printf("Total: $%.2f\n", ((item1.itemPrice*item1.itemQuantity)+(item2.itemPrice*item2.itemQuantity)));

}
