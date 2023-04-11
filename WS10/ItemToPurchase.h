#ifndef ItemToPurchase_H
#define ItemToPurchase_H

typedef struct ItemToPurchase{
    char itemName[50];
    int itemQuantity;
    double itemPrice;
} ItemToPurchase;

void MakeItemBlank(ItemToPurchase* itemTemp);

void PrintItemCost(ItemToPurchase item1, ItemToPurchase item2);
#endif
