#ifndef _INV
#define _INV

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    char* data;
    struct Node* next;
};

struct LList {
    struct Node* head;
};

void initializeInventory(struct LList* inventory);
int hasItem(const struct LList* inventory, const char* item);
void addItem(struct LList* inventory, const char* item);
void removeItem(struct LList* inventory, const char* item);
void cleanupInventory(struct LList* inventory);
#endif