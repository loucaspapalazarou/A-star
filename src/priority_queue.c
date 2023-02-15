#include <stdlib.h>
#include <stdio.h>

typedef struct
{
    int x;
    int y;
    double cost;
} point;

typedef struct
{
    point *heap;
    int capacity;
    int size;
} priority_queue;

priority_queue *create_priority_queue(int capacity)
{
    priority_queue *pq = malloc(sizeof(priority_queue));
    pq->heap = malloc(sizeof(point) * (capacity + 1));
    pq->capacity = capacity;
    pq->size = 0;
    return pq;
}

void destroy_priority_queue(priority_queue *pq)
{
    free(pq->heap);
    free(pq);
}

void swap(point *a, point *b)
{
    point temp = *a;
    *a = *b;
    *b = temp;
}

void min_heapify(point *heap, int i, int n)
{
    int left = 2 * i;
    int right = 2 * i + 1;
    int smallest = i;
    if (left <= n && heap[left].cost < heap[smallest].cost)
    {
        smallest = left;
    }
    if (right <= n && heap[right].cost < heap[smallest].cost)
    {
        smallest = right;
    }
    if (smallest != i)
    {
        swap(&heap[i], &heap[smallest]);
        min_heapify(heap, smallest, n);
    }
}

void build_min_heap(point *heap, int n)
{
    for (int i = n / 2; i >= 1; i--)
    {
        min_heapify(heap, i, n);
    }
}

void enqueue(priority_queue *pq, point value)
{
    if (pq->size == pq->capacity)
    {
        fprintf(stderr, "Priority queue is full\n");
        exit(1);
    }
    pq->size++;
    pq->heap[pq->size] = value;
    int i = pq->size;
    while (i > 1 && pq->heap[i].cost < pq->heap[i / 2].cost)
    {
        swap(&pq->heap[i], &pq->heap[i / 2]);
        i /= 2;
    }
}

point dequeue(priority_queue *pq)
{
    if (pq->size == 0)
    {
        fprintf(stderr, "Priority queue is empty\n");
        exit(1);
    }
    point min_value = pq->heap[1];
    pq->heap[1] = pq->heap[pq->size];
    pq->size--;
    min_heapify(pq->heap, 1, pq->size);
    return min_value;
}

int is_empty(priority_queue *pq)
{
    return pq->size == 0;
}

int size(priority_queue *pq)
{
    return pq->size;
}

void print_priority_queue(priority_queue *pq)
{
    if (is_empty(pq))
    {
        printf("Priority queue is empty.\n");
        return;
    }
    for (int i = 1; i <= pq->size; i++)
    {
        printf("(%d, %d, %f)\n", pq->heap[i].x, pq->heap[i].y, pq->heap[i].cost);
    }
}
