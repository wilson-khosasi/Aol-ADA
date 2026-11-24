#include <stdio.h>
#include "priorityQueue.h"

int main(){
    priorityQueue *pq = createPriorityQueue(5);

    if(pq == NULL){
        printf("Failed to create Priority Queue\n");
        return 1;
    }

    // Insert some elements
    insert(pq, 10, 30);
    insert(pq, 20, 10);
    insert(pq, 15, 20);
    insert(pq, 5, 5);
    insert(pq, 25, 15);

    // Display the heap array
    printf("Priority Queue:\n");

    for(int i = 0; i < pq->size; i++){
        printf("Index %d: Vertex = %d, Priority = %d\n",
               i, pq->nodes[i].vertex, pq->nodes[i].priority);
    }

    return 0;
}