#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
    struct Node* prev;
};

// Create node
struct Node* createNode(int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->next = newNode->prev = NULL;
    return newNode;
}

// Insert in empty list
void insertEmpty(struct Node** head, int value) {
    struct Node* newNode = createNode(value);

    *head = newNode;
    newNode->next = newNode;
    newNode->prev = newNode;
}

// Insert at end
void insertEnd(struct Node** head, int value) {
    if (*head == NULL) {
        insertEmpty(head, value);
        return;
    }

    struct Node* newNode = createNode(value);
    struct Node* last = (*head)->prev;

    last->next = newNode;
    newNode->prev = last;

    newNode->next = *head;
    (*head)->prev = newNode;
}

// Insert at beginning
void insertBeginning(struct Node** head, int value) {
    if (*head == NULL) {
        insertEmpty(head, value);
        return;
    }

    struct Node* newNode = createNode(value);
    struct Node* last = (*head)->prev;

    newNode->next = *head;
    newNode->prev = last;

    last->next = newNode;
    (*head)->prev = newNode;

    *head = newNode;
}

// Delete a node
void deleteNode(struct Node** head, int value) {
    if (*head == NULL) return;

    struct Node *curr = *head, *temp;

    // single node
    if (curr->next == *head && curr->data == value) {
        free(curr);
        *head = NULL;
        return;
    }

    do {
        if (curr->data == value) {
            curr->prev->next = curr->next;
            curr->next->prev = curr->prev;

            if (curr == *head)
                *head = curr->next;

            free(curr);
            return;
        }
        curr = curr->next;
    } while (curr != *head);
}

// Display forward
void display(struct Node* head) {
    if (head == NULL) {
        printf("List is empty\n");
        return;
    }

    struct Node* temp = head;

    printf("Forward: ");
    do {
        printf("%d <-> ", temp->data);
        temp = temp->next;
    } while (temp != head);

    printf("(back to head)\n");
}

// Main
int main() {
    struct Node* head = NULL;

    insertEnd(&head, 10);
    insertEnd(&head, 20);
    insertEnd(&head, 30);

    printf("Circular Doubly Linked List:\n");
    display(head);

    insertBeginning(&head, 5);
    printf("\nAfter inserting 5 at beginning:\n");
    display(head);

    deleteNode(&head, 20);
    printf("\nAfter deleting 20:\n");
    display(head);

    return 0;
}
