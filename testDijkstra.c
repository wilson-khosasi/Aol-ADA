#include <assert.h>
#include <stdio.h>

#include "dijkstra.h"

static void printPath(const int *path, int pathLength) {
    for (int i = 0; i < pathLength; i++) {
        printf("%d", path[i]);
        if (i + 1 < pathLength) {
            printf(" -> ");
        }
    }
    printf("\n");
}

int main(void) {
    /*
     * Edge weights below represent travel time units (for example, minutes).
     * addEdge() creates an undirected edge in this project's Graph module.
     */
    Graph *graph = createGraph(6);
    assert(graph != NULL);

    addEdge(graph, 0, 1, 10);
    addEdge(graph, 0, 2, 3);
    addEdge(graph, 1, 2, 1);
    addEdge(graph, 1, 3, 2);
    addEdge(graph, 2, 3, 8);
    addEdge(graph, 2, 4, 2);
    addEdge(graph, 3, 4, 7);
    /* Vertex 5 is intentionally disconnected from the other vertices. */

    DijkstraResult *result = dijkstra(graph, 0);
    assert(result != NULL);

    /* Expected shortest travel times from source vertex 0. */
    assert(result->dist[0] == 0);
    assert(result->dist[1] == 4);
    assert(result->dist[2] == 3);
    assert(result->dist[3] == 6);
    assert(result->dist[4] == 5);
    assert(result->dist[5] == DIJKSTRA_INF);

    printf("Shortest travel times from vertex 0:\n");
    for (int v = 0; v < result->numVertices; v++) {
        if (result->dist[v] == DIJKSTRA_INF) {
            printf("To %d: unreachable\n", v);
        } else {
            printf("To %d: %d time units\n", v, result->dist[v]);
        }
    }

    int path[6];
    int pathLength = reconstructPath(result, 3, path, 6);
    assert(pathLength == 4);

    printf("\nShortest path from 0 to 3: ");
    printPath(path, pathLength);
    printf("Total travel time: %d time units\n", result->dist[3]);

    /* An unreachable destination must return 0. */
    assert(reconstructPath(result, 5, path, 6) == 0);

    /* Invalid source must be rejected. */
    assert(dijkstra(graph, 6) == NULL);

    freeDijkstraResult(result);
    freeGraph(graph);

    printf("\nAll Dijkstra tests passed.\n");
    return 0;
}
