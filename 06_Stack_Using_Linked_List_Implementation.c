#include <stdio.h>
#include <stdlib.h>

// Node structure
struct Node {
    int data;
    struct Node* next;
};

// Top pointer
struct Node* top = NULL;

// Check if stack is empty
int isEmpty() {
    return top == NULL;
}

// Push operation
void push(int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));

    if (newNode == NULL) {
        printf("Stack Overflow\n");
        return;
    }

    newNode->data = value;
    newNode->next = top;
    top = newNode;

    printf("%d pushed to stack\n", value);
}

// Pop operation
int pop() {
    if (isEmpty()) {
        printf("Stack Underflow\n");
        return -1;
    }

    struct Node* temp = top;
    int popped = temp->data;
    top = top->next;

    free(temp);
    return popped;
}

// Peek operation
int peek() {
    if (isEmpty()) {
        printf("Stack is empty\n");
        return -1;
    }
    return top->data;
}

// Display stack
void display() {
    struct Node* temp = top;

    if (isEmpty()) {
        printf("Stack is empty\n");
        return;
    }

    printf("Stack elements: ");
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

// Main function
int main() {
    push(10);
    push(20);
    push(30);

    display();

    printf("Top element: %d\n", peek());

    printf("Popped: %d\n", pop());
    display();

    printf("Popped: %d\n", pop());
    display();

    return 0;
}
