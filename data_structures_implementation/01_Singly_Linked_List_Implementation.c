#include <stdio.h>
#include <stdlib.h>

// Node structure
struct Node {
    int data;
    struct Node* next;
};

// Create node
struct Node* createNode(int value) {
    struct Node* newNode = malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->next = NULL;
    return newNode;
}

// Insert at beginning
void insertBeginning(struct Node** head, int value) {
    struct Node* newNode = createNode(value);
    newNode->next = *head;
    *head = newNode;
}

// Insert at end
void insertEnd(struct Node** head, int value) {
    struct Node* newNode = createNode(value);

    if (*head == NULL) {
        *head = newNode;
        return;
    }

    struct Node* temp = *head;
    while (temp->next != NULL)
        temp = temp->next;

    temp->next = newNode;
}

// Insert at position
void insertAtPosition(struct Node** head, int value, int pos) {
    if (pos == 1) {
        insertBeginning(head, value);
        return;
    }

    struct Node* temp = *head;
    for (int i = 1; i < pos - 1 && temp != NULL; i++)
        temp = temp->next;

    if (temp == NULL) return;

    struct Node* newNode = createNode(value);
    newNode->next = temp->next;
    temp->next = newNode;
}

// Delete at position
void deleteAtPosition(struct Node** head, int pos) {
    if (*head == NULL) return;

    struct Node* temp = *head;

    if (pos == 1) {
        *head = temp->next;
        free(temp);
        return;
    }

    for (int i = 1; i < pos - 1 && temp->next != NULL; i++)
        temp = temp->next;

    if (temp->next == NULL) return;

    struct Node* del = temp->next;
    temp->next = del->next;
    free(del);
}

// Search
int search(struct Node* head, int key) {
    int pos = 1;
    while (head != NULL) {
        if (head->data == key)
            return pos;
        head = head->next;
        pos++;
    }
    return -1;
}

// Size
int size(struct Node* head) {
    int count = 0;
    while (head != NULL) {
        count++;
        head = head->next;
    }
    return count;
}

// Reverse
struct Node* reverse(struct Node* head) {
    struct Node *prev = NULL, *curr = head, *next;

    while (curr != NULL) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    return prev;
}

// Display
void display(struct Node* head) {
    while (head != NULL) {
        printf("%d -> ", head->data);
        head = head->next;
    }
    printf("NULL\n");
}

// MAIN (tests everything)
int main() {
    struct Node* head = NULL;

    insertBeginning(&head, 10);
    insertBeginning(&head, 20);
    insertEnd(&head, 30);
    insertEnd(&head, 40);

    printf("Initial List:\n");
    display(head);

    insertAtPosition(&head, 25, 3);
    printf("\nAfter insert 25 at pos 3:\n");
    display(head);

    deleteAtPosition(&head, 2);
    printf("\nAfter delete pos 2:\n");
    display(head);

    int pos = search(head, 30);
    printf("\nSearch 30 → Position: %d\n", pos);

    printf("Size: %d\n", size(head));

    head = reverse(head);
    printf("\nAfter reverse:\n");
    display(head);

    return 0;
}
