#include <stdio.h>
#include <stdlib.h>

// Node structure
struct Node {
    int data;
    struct Node* next;
    struct Node* prev;
};

// Create node
struct Node* createNode(int value) {
    struct Node* n = malloc(sizeof(struct Node));
    n->data = value;
    n->next = NULL;
    n->prev = NULL;
    return n;
}

// Insert at beginning
void insertBeginning(struct Node** head, int value) {
    struct Node* newNode = createNode(value);

    if (*head != NULL) {
        newNode->next = *head;
        (*head)->prev = newNode;
    }

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
    newNode->prev = temp;
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
    newNode->prev = temp;

    if (temp->next != NULL)
        temp->next->prev = newNode;

    temp->next = newNode;
}

// Delete at position
void deleteAtPosition(struct Node** head, int pos) {
    if (*head == NULL) return;

    struct Node* temp = *head;

    if (pos == 1) {
        *head = temp->next;
        if (*head != NULL)
            (*head)->prev = NULL;
        free(temp);
        return;
    }

    for (int i = 1; i < pos && temp != NULL; i++)
        temp = temp->next;

    if (temp == NULL) return;

    if (temp->prev != NULL)
        temp->prev->next = temp->next;

    if (temp->next != NULL)
        temp->next->prev = temp->prev;

    free(temp);
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

// Reverse list
struct Node* reverse(struct Node* head) {
    struct Node* temp = NULL;
    struct Node* curr = head;

    while (curr != NULL) {
        temp = curr->prev;
        curr->prev = curr->next;
        curr->next = temp;
        curr = curr->prev;
    }

    if (temp != NULL)
        head = temp->prev;

    return head;
}

// Display forward
void displayForward(struct Node* head) {
    printf("Forward: ");
    while (head != NULL) {
        printf("%d <-> ", head->data);
        head = head->next;
    }
    printf("NULL\n");
}

// Display backward
void displayBackward(struct Node* head) {
    if (head == NULL) return;

    struct Node* temp = head;

    while (temp->next != NULL)
        temp = temp->next;

    printf("Backward: ");
    while (temp != NULL) {
        printf("%d <-> ", temp->data);
        temp = temp->prev;
    }
    printf("NULL\n");
}

// MAIN
int main() {
    struct Node* head = NULL;

    insertBeginning(&head, 20);
    insertBeginning(&head, 10);
    insertEnd(&head, 30);
    insertEnd(&head, 40);

    printf("Initial list:\n");
    displayForward(head);
    displayBackward(head);

    insertAtPosition(&head, 25, 3);
    printf("\nAfter insert 25 at pos 3:\n");
    displayForward(head);

    deleteAtPosition(&head, 2);
    printf("\nAfter delete pos 2:\n");
    displayForward(head);

    printf("\nSize: %d\n", size(head));

    int pos = search(head, 30);
    printf("Search 30 → position: %d\n", pos);

    head = reverse(head);
    printf("\nAfter reverse:\n");
    displayForward(head);

    return 0;
}
