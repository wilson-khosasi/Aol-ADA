#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "graph.h"


int main(){
    srand((unsigned)time(NULL));
    Graph *graph = createGraph(NUM_VERTICES);

    if(graph == NULL){
        printf("Failed to create graph\n");
        return 1;
    }

    generateGrid(graph);

    for(int i = 0; i < NUM_VERTICES; i++){
        printf("Vertex %d connection:\n", i);
        
        Node *curr = graph->vertices[i].head;
        while(curr != NULL){
            printf(" -> %d (weight: %d)", curr->dest, curr->weight);
            curr = curr->next;
        }
        printf("\n");
    }

    freeGraph(graph);

    return 0;
}