#include <stdio.h>
#include <stdlib.h>

#include "priorityQueue.h"

priorityQueue *createPriorityQueue(int initCapacity){
    if(initCapacity <= 0){
        return NULL;
    }
    
    priorityQueue *pq = malloc(sizeof(*pq));

    if(pq == NULL){
        return NULL;
    }

    pq->nodes = malloc(initCapacity * sizeof(heapNode));

    if(pq->nodes == NULL){
        free(pq);
        return NULL;
    }

    pq->size = 0;
    pq->capacity = initCapacity;

    return pq;
}

static void heapifyUp(priorityQueue *pq, int index){
    while(index > 0){
        int parent = (index - 1)/2;

        if(pq->nodes[index].priority > pq->nodes[parent].priority){
            return;
        }

        heapNode temp = pq->nodes[index];
        pq->nodes[index] = pq->nodes[parent];
        pq->nodes[parent] = temp;

        index = parent;
    }
}

int insert(priorityQueue *pq, int vertex, int priority){
    // untuk 0 gagal, 1 sukses
    if(pq == NULL){
        return 0;
    }

    // cheak jika array heap sudah penuh
    if(pq->size == pq->capacity){
        return 0;
    }

    // initiatlize data yang mau diinsert
    heapNode newNode;
    newNode.vertex = vertex;
    newNode.priority = priority;

    //insert ke heap
    pq->nodes[pq->size] = newNode;
    //increase nilai size untuk insert selanjutnya
    pq->size += 1;

    // untuk menjaga heap property
    heapifyUp(pq, pq->size - 1);

    return 1;
}