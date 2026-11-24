#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

typedef struct {
    int vertex;
    int priority;
} heapNode;

typedef struct {
    heapNode *nodes;
    int size;
    int capacity;
} priorityQueue;

priorityQueue *createPriorityQueue(int initCapacity);
int insert(priorityQueue *pq, int vertex, int priority);
int extractMin(priorityQueue *pq, heapNode *minNode);
int isEmpty(priorityQueue *pq);
void freePriorityQueue(priorityQueue *pq);

#endif