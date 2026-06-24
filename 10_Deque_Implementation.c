#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* ================= NODE ================= */

typedef struct Node {
    int data;
    struct Node *prev;
    struct Node *next;
} Node;

/* ================= DEQUE ================= */

typedef struct Deque {
    Node *front;
    Node *back;
    int size;
} Deque;

/* ================= HELPERS ================= */

Node *createNode(int value)
{
    Node *node = (Node *)malloc(sizeof(Node));
    node->data = value;
    node->prev = NULL;
    node->next = NULL;
    return node;
}

Deque *createDeque(void)
{
    Deque *dq = (Deque *)malloc(sizeof(Deque));
    dq->front = NULL;
    dq->back = NULL;
    dq->size = 0;
    return dq;
}

bool isEmpty(Deque *dq)
{
    return dq->size == 0;
}

/* ================= PUSH ================= */

void pushFront(Deque *dq, int value)
{
    Node *node = createNode(value);

    if (isEmpty(dq)) {
        dq->front = node;
        dq->back = node;
    } else {
        node->next = dq->front;
        dq->front->prev = node;
        dq->front = node;
    }

    dq->size++;
}

void pushBack(Deque *dq, int value)
{
    Node *node = createNode(value);

    if (isEmpty(dq)) {
        dq->front = node;
        dq->back = node;
    } else {
        node->prev = dq->back;
        dq->back->next = node;
        dq->back = node;
    }

    dq->size++;
}

/* ================= POP ================= */

int popFront(Deque *dq)
{
    if (isEmpty(dq)) {
        printf("Deque is empty\n");
        return -1;
    }

    Node *temp = dq->front;
    int value = temp->data;

    dq->front = dq->front->next;

    if (dq->front)
        dq->front->prev = NULL;
    else
        dq->back = NULL;

    free(temp);
    dq->size--;

    return value;
}

int popBack(Deque *dq)
{
    if (isEmpty(dq)) {
        printf("Deque is empty\n");
        return -1;
    }

    Node *temp = dq->back;
    int value = temp->data;

    dq->back = dq->back->prev;

    if (dq->back)
        dq->back->next = NULL;
    else
        dq->front = NULL;

    free(temp);
    dq->size--;

    return value;
}

/* ================= ACCESS ================= */

int getFront(Deque *dq)
{
    if (isEmpty(dq))
        return -1;
    return dq->front->data;
}

int getBack(Deque *dq)
{
    if (isEmpty(dq))
        return -1;
    return dq->back->data;
}

/* ================= DISPLAY ================= */

void printDeque(Deque *dq)
{
    Node *cur = dq->front;

    printf("Deque: ");
    while (cur) {
        printf("%d ", cur->data);
        cur = cur->next;
    }
    printf("\n");
}

/* ================= CLEANUP ================= */

void freeDeque(Deque *dq)
{
    while (!isEmpty(dq))
        popFront(dq);
    free(dq);
}

/* ================= TEST ================= */

int main(void)
{
    Deque *dq = createDeque();

    pushBack(dq, 10);
    pushBack(dq, 20);
    pushFront(dq, 5);
    pushFront(dq, 1);

    printDeque(dq);      // 1 5 10 20
    printf("Front = %d\n", getFront(dq));
    printf("Back  = %d\n", getBack(dq));

    printf("popFront = %d\n", popFront(dq));
    printf("popBack  = %d\n", popBack(dq));

    printDeque(dq);      // 5 10

    freeDeque(dq);
    return 0;
}
