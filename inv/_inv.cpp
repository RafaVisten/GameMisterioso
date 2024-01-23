#include "_inv.hpp"

void initializeInventory(struct LList* inventory) {
    inventory->head = NULL;
}

int hasItem(const struct LList* inventory, const char* item) {
    const struct Node* current = inventory->head;
    while (current != NULL) {
        if (strcmp(current->data, item) == 0) {
            return 1;  // Item found
        }
        current = current->next;
    }
    return 0;  // Item not found
}

void addItem(struct LList* inventory, const char* item) {
    if (!hasItem(inventory, item)) {
        struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
        if (newNode == NULL) {
            fprintf(stderr, "Memory allocation failed.\n");
            exit(EXIT_FAILURE);
        }

        newNode->data = strdup(item);
        if (newNode->data == NULL) {
            fprintf(stderr, "Memory allocation failed.\n");
            free(newNode);
            exit(EXIT_FAILURE);
        }

        newNode->next = inventory->head;
        inventory->head = newNode;

        printf("%s added to the inventory.\n", item);
    } else {
        printf("Item already exists in the inventory.\n");
    }
}

void removeItem(struct LList* inventory, const char* item) {
    struct Node* current = inventory->head;
    struct Node* prev = NULL;

    while (current != NULL) {
        if (strcmp(current->data, item) == 0) {
            if (prev == NULL) {
                inventory->head = current->next;
            } else {
                prev->next = current->next;
            }

            free(current->data);
            free(current);

            printf("%s removed from the inventory.\n", item);
            return;
        }

        prev = current;
        current = current->next;
    }

    printf("Item not found in the inventory.\n");
}

void cleanupInventory(struct LList* inventory) {
    struct Node* current = inventory->head;
    struct Node* nextNode;

    while (current != NULL) {
        nextNode = current->next;
        free(current->data);
        free(current);
        current = nextNode;
    }
}
