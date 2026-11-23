#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

Graph *createGraph(int numVertices){
    Graph *graph = malloc(sizeof(Graph));

    if(graph == NULL){
        return NULL;
    }

    graph->numVertices = numVertices;

    graph->vertices = malloc(numVertices * sizeof(Vertex));

    if(graph->vertices == NULL){
        free(graph);
        return NULL;
    }

    for(int i = 0; i < numVertices; i++){
        graph->vertices[i].head = NULL;
    }

    return graph;
}

static void insertNode(Vertex *vertex, int destination, int weight){
    Node *newNode = malloc(sizeof(*newNode));

    if(newNode == NULL){
        return;
    }

    newNode->dest = destination;
    newNode->weight = weight;

    newNode->next = vertex->head;
    vertex->head = newNode;
}

void addEdge(Graph *graph, int source, int destination, int weight){
    if(graph == NULL){
        return;
    }

    if(source < 0 || source >= graph->numVertices || destination >= graph->numVertices || destination < 0){
        return;
    }
    // tambah adjacency list di vertex source
    insertNode(&graph->vertices[source], destination, weight);
    // tambah adjacency list di vertex destination
    insertNode(&graph->vertices[destination], source, weight);
}

void freeGraph(Graph *graph){
    if(graph == NULL){
        return;
    }
    //free linked list Node dulu
    for(int i = 0; i < graph->numVertices; i++){
        Node *curr = graph->vertices[i].head;

        while(curr != NULL){
            Node *temp = curr;
            curr = curr->next;
            free(temp);
        }
    }
    // baru free vertices sama gridnya. 
    // Harus in this order, kalo gak kita bisa kehilangan pointer ke mereka
    free(graph->vertices);
    free(graph);
}

void generateGrid(Graph *graph){
    if(graph == NULL){
        return;
    }
    for(int i = 0; i < NUM_VERTICES; i++){
        int row = i / GRID_SIZE;
        int col = i % GRID_SIZE;

        // connect ke kanan
        if(col < GRID_SIZE - 1){
            addEdge(graph, i, i+1, rand() % 10 + 1);
        }

        // connect ke bawah
        if(row < GRID_SIZE - 1){
            addEdge(graph, i, i+5, rand() % 10 + 1);
        }
    }
}