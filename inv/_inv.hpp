#ifndef _INV
#define _INV

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    char* data;
    struct Node* next;
};

struct PlayerInventory {
    struct Node* head;
};

void initializeInventory(struct PlayerInventory* inventory);
int hasItem(const struct PlayerInventory* inventory, const char* item);
void addItem(struct PlayerInventory* inventory, const char* item);
void removeItem(struct PlayerInventory* inventory, const char* item);
void cleanupInventory(struct PlayerInventory* inventory);
#endif