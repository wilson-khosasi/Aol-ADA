#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

Graph *createGraph(int numVertices){
    if(numVertices <= 0){
        return NULL;
    }
    Graph *graph = malloc(sizeof(*graph));

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

static Node *createNode(int destination, int weight){
    Node *newNode = malloc(sizeof(*newNode));

    if(newNode == NULL){
        return NULL;
    }

    newNode->dest = destination;
    newNode->weight = weight;

    newNode->next = NULL;

    return newNode;
}

void addEdge(Graph *graph, int source, int destination, int weight){
    if(graph == NULL){
        return;
    }

    if(source < 0 || source >= graph->numVertices || destination >= graph->numVertices || destination < 0 || weight <= 0 || source == destination){
        return;
    }

    //alokasi satu satu
    //di algo sebelumnya, kalo ad gagal alokasi, gak kedetect, bisa jadi directed edge nanti
    Node *depan = createNode(destination, weight);
    Node *belakang = createNode(source, weight);

    if(depan == NULL || belakang == NULL){ //hanya jika kedua nya return tidak null, baru di insert
        free(depan);
        free(belakang);
        return;
    }

    // tambah adjacency list di vertex source
    depan->next = graph->vertices[source].head;
    graph->vertices[source].head = depan;

    // tambah adjacency list di vertex destination
    belakang->next = graph->vertices[destination].head;
    graph->vertices[destination].head = belakang;
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
            addEdge(graph, i, i+GRID_SIZE, rand() % 10 + 1);
        }
    }
}