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

    // verif keakuratan graph yang dibuat
    int totalEntries = 0;
    int invalidWeights = 0;

    for (int i = 0; i < NUM_VERTICES; i++) {
        Node *curr = graph->vertices[i].head;

        while (curr != NULL) {
            totalEntries++;

            if (curr->weight < 1 || curr->weight > 10) {
                invalidWeights++;
            }

            curr = curr->next;
        }
    }
    printf("\n--- Graph Verification ---\n");
    printf("Vertices: %d\n", graph->numVertices);
    printf("Adjacency entries: %d\n", totalEntries);
    printf("Undirected edges: %d\n", totalEntries / 2);
    printf("Invalid weights: %d\n", invalidWeights);

    // cheak apakah ad yang hubungan undirected graph sudah benar
    int mismatches = 0;
    for(int i = 0; i < graph->numVertices; i++){
        Node *curr = graph->vertices[i].head;

        while(curr != NULL){
            int found = 0;
            Node *reverse = graph->vertices[curr->dest].head;

            while(reverse != NULL){
                if(reverse->dest == i &&
                reverse->weight == curr->weight){
                    found = 1;
                    break;
                }

                reverse = reverse->next;
            }

            if(!found){
                mismatches++;
            }

            curr = curr->next;
        }
    }

    printf("Mismatched reverse edges: %d\n", mismatches);

    // print list adjacency list
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