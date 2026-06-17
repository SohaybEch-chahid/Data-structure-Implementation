#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

// Create node
struct Node* createNode(int value) {
    struct Node* n = malloc(sizeof(struct Node));
    n->data = value;
    n->next = NULL;
    return n;
}

// Insert at end
void insertEnd(struct Node** head, int value) {
    struct Node* newNode = createNode(value);

    if (*head == NULL) {
        *head = newNode;
        newNode->next = *head;
        return;
    }

    struct Node* temp = *head;
    while (temp->next != *head)
        temp = temp->next;

    temp->next = newNode;
    newNode->next = *head;
}

// Insert at beginning
void insertBeginning(struct Node** head, int value) {
    struct Node* newNode = createNode(value);

    if (*head == NULL) {
        *head = newNode;
        newNode->next = *head;
        return;
    }

    struct Node* temp = *head;
    while (temp->next != *head)
        temp = temp->next;

    newNode->next = *head;
    temp->next = newNode;
    *head = newNode;
}

// Size
int size(struct Node* head) {
    if (head == NULL) return 0;

    int count = 0;
    struct Node* temp = head;

    do {
        count++;
        temp = temp->next;
    } while (temp != head);

    return count;
}

// Search
int search(struct Node* head, int key) {
    if (head == NULL) return -1;

    int pos = 1;
    struct Node* temp = head;

    do {
        if (temp->data == key)
            return pos;
        temp = temp->next;
        pos++;
    } while (temp != head);

    return -1;
}

// Insert at position
void insertAtPosition(struct Node** head, int value, int pos) {
    if (pos == 1) {
        insertBeginning(head, value);
        return;
    }

    struct Node* temp = *head;
    for (int i = 1; i < pos - 1 && temp->next != *head; i++)
        temp = temp->next;

    struct Node* newNode = createNode(value);
    newNode->next = temp->next;
    temp->next = newNode;
}

// Delete at position
void deleteAtPosition(struct Node** head, int pos) {
    if (*head == NULL) return;

    struct Node* temp = *head;

    // delete head
    if (pos == 1) {
        if (temp->next == *head) {
            free(temp);
            *head = NULL;
            return;
        }

        struct Node* last = *head;
        while (last->next != *head)
            last = last->next;

        *head = temp->next;
        last->next = *head;
        free(temp);
        return;
    }

    for (int i = 1; i < pos - 1 && temp->next != *head; i++)
        temp = temp->next;

    struct Node* del = temp->next;
    temp->next = del->next;
    free(del);
}

// Reverse (tricky!)
struct Node* reverse(struct Node* head) {
    if (head == NULL || head->next == head)
        return head;

    struct Node *prev = NULL, *curr = head, *next;
    struct Node* first = head;

    do {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    } while (curr != first);

    first->next = prev;
    return prev;
}

// Display
void display(struct Node* head) {
    if (head == NULL) {
        printf("Empty\n");
        return;
    }

    struct Node* temp = head;
    do {
        printf("%d -> ", temp->data);
        temp = temp->next;
    } while (temp != head);

    printf("(back to head)\n");
}

// MAIN
int main() {
    struct Node* head = NULL;

    insertEnd(&head, 10);
    insertEnd(&head, 20);
    insertEnd(&head, 30);

    printf("Initial:\n");
    display(head);

    insertBeginning(&head, 5);
    printf("\nAfter insert at beginning:\n");
    display(head);

    insertAtPosition(&head, 15, 3);
    printf("\nAfter insert 15 at pos 3:\n");
    display(head);

    deleteAtPosition(&head, 2);
    printf("\nAfter delete pos 2:\n");
    display(head);

    printf("\nSize: %d\n", size(head));

    int pos = search(head, 30);
    printf("Search 30 → %d\n", pos);

    head = reverse(head);
    printf("\nAfter reverse:\n");
    display(head);

    return 0;
}
