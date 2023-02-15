#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

struct point
{
    int x;
    int y;
    double cost;
    struct point *previous;
};

typedef struct point point;

typedef struct
{
    point **heap;
    int capacity;
    int size;
} priority_queue;

priority_queue *create_priority_queue(int capacity);

void destroy_priority_queue(priority_queue *pq);

void enqueue(priority_queue *pq, point *value);

point *dequeue(priority_queue *pq);

int is_empty(priority_queue *pq);

int size(priority_queue *pq);

void print_priority_queue(priority_queue *pq);

#endif
