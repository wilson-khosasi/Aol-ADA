#ifndef GRAPH_H
#define GRAPH_H
#define GRID_SIZE 5
#define NUM_VERTICES (GRID_SIZE * GRID_SIZE)

// representasi koneksi 1 node ke node lain
typedef struct Node{
    int dest;
    int weight;
    struct Node *next;
} Node;

// representasi satu node dan adjacency list nya
typedef struct {
    Node *head;
} Vertex;

// representasi seluruh graph
typedef struct  {
    int numVertices;
    Vertex *vertices;
} Graph;

Graph *createGraph(int numVertices);
void addEdge(Graph *graph, int source, int destination, int weight);

#endif