#include <stdio.h>
#include <stdlib.h>

#include "graph.h"


int main(){
    Graph *graph = createGraph(3);

    if(graph == NULL){
        printf("Failed to create graph\n");
        return 1;
    }

    addEdge(graph, 0, 1, 6);
    addEdge(graph, 0, 2, 8);
    // generateGrid(graph);

    for(int i = 0; i < 3; i++){
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