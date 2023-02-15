#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

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

priority_queue *create_priority_queue(int capacity);
void destroy_priority_queue(priority_queue *pq);
void enqueue(priority_queue *pq, point value);
point dequeue(priority_queue *pq);
int is_empty(priority_queue *pq);
int size(priority_queue *pq);
void print_priority_queue(priority_queue *pq);

#endif
