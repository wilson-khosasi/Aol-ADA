#include <stdio.h>
#include "priorityQueue.h"

int main() {
    priorityQueue *pq = createPriorityQueue(5);

    if (pq == NULL) {
        printf("Failed to create priority queue\n");
        return 1;
    }

    printf("Priority Queue created successfully!\n");
    printf("Size: %d\n", pq->size);
    printf("Capacity: %d\n", pq->capacity);

    // freePriorityQueue(pq);

    return 0;
}