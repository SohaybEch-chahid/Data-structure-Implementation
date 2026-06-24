#include <stdio.h>

#define SIZE 100

int heap[SIZE];
int heapSize = 0;

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void insert(int value)
{
    int i = heapSize;
    heap[i] = value;
    heapSize++;

    while (i != 0 && heap[(i - 1) / 2] > heap[i])
    {
        swap(&heap[(i - 1) / 2], &heap[i]);
        i = (i - 1) / 2;
    }
}

void heapifyDown(int i)
{
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < heapSize && heap[left] < heap[smallest])
        smallest = left;

    if (right < heapSize && heap[right] < heap[smallest])
        smallest = right;

    if (smallest != i)
    {
        swap(&heap[i], &heap[smallest]);
        heapifyDown(smallest);
    }
}

int extractMin()
{
    if (heapSize <= 0)
        return -1;

    int root = heap[0];

    heap[0] = heap[heapSize - 1];
    heapSize--;

    heapifyDown(0);

    return root;
}

void printHeap()
{
    for (int i = 0; i < heapSize; i++)
        printf("%d ", heap[i]);

    printf("\n");
}

int main()
{
    insert(5);
    insert(2);
    insert(8);
    insert(1);

    printHeap();

    printf("Min = %d\n", extractMin());

    printHeap();
}
