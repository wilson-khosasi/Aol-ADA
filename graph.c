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