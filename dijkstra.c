#include <limits.h>
#include <stdlib.h>

#include "dijkstra.h"

/*
 * Selects the unvisited vertex with the smallest tentative travel time.
 * Returns -1 if no reachable unvisited vertex remains.
 *
 * This O(V) scan temporarily replaces EXTRACT_MIN from the shared Priority
 * Queue. It can be removed when priority_queue.h/.c is ready.
 */
static int findMinUnvisited(
    const int *dist,
    const int *visited,
    int numVertices
) {
    int minVertex = -1;
    int minDistance = DIJKSTRA_INF;

    for (int v = 0; v < numVertices; v++) {
        if (!visited[v] && dist[v] < minDistance) {
            minDistance = dist[v];
            minVertex = v;
        }
    }

    return minVertex;
}

DijkstraResult *dijkstra(const Graph *graph, int source) {
    if (graph == NULL || graph->vertices == NULL || graph->numVertices <= 0) {
        return NULL;
    }

    const int n = graph->numVertices;

    if (source < 0 || source >= n) {
        return NULL;
    }

    DijkstraResult *result = malloc(sizeof(*result));
    if (result == NULL) {
        return NULL;
    }

    int *visited = calloc((size_t)n, sizeof(*visited));
    result->dist = malloc((size_t)n * sizeof(*result->dist));
    result->prev = malloc((size_t)n * sizeof(*result->prev));

    if (visited == NULL || result->dist == NULL || result->prev == NULL) {
        free(visited);
        free(result->dist);
        free(result->prev);
        free(result);
        return NULL;
    }

    result->numVertices = n;
    result->source = source;

    /* Initialization: all vertices are initially unreachable. */
    for (int v = 0; v < n; v++) {
        result->dist[v] = DIJKSTRA_INF;
        result->prev[v] = -1;
    }
    result->dist[source] = 0;

    /*
     * Ordinary Dijkstra using a linear minimum search.
     * Later, the findMinUnvisited() step will be replaced by the team's
     * shared Priority Queue operations.
     */
    for (int iteration = 0; iteration < n; iteration++) {
        int u = findMinUnvisited(result->dist, visited, n);

        /* No reachable unvisited vertex remains. */
        if (u == -1) {
            break;
        }

        visited[u] = 1;

        /* Relax every outgoing edge from u. */
        for (Node *edge = graph->vertices[u].head;
             edge != NULL;
             edge = edge->next) {

            int v = edge->dest;
            int travelTime = edge->weight;

            /* Defensive checks in case the graph was modified manually. */
            if (v < 0 || v >= n || travelTime < 0) {
                free(visited);
                freeDijkstraResult(result);
                return NULL;
            }

            /*
             * Avoid integer overflow and do not process finalized vertices.
             * For a non-negative weighted graph, a finalized vertex cannot
             * receive a better distance later.
             */
            if (!visited[v] &&
                result->dist[u] != DIJKSTRA_INF &&
                result->dist[u] <= INT_MAX - travelTime) {

                int newDistance = result->dist[u] + travelTime;

                if (newDistance < result->dist[v]) {
                    result->dist[v] = newDistance;
                    result->prev[v] = u;
                }
            }
        }
    }

    free(visited);
    return result;
}

int reconstructPath(
    const DijkstraResult *result,
    int destination,
    int *path,
    int pathCapacity
) {
    if (result == NULL || result->dist == NULL || result->prev == NULL ||
        path == NULL || pathCapacity <= 0 ||
        destination < 0 || destination >= result->numVertices) {
        return -1;
    }

    if (result->dist[destination] == DIJKSTRA_INF) {
        return 0;
    }

    /* First collect the path backwards: destination -> source. */
    int count = 0;
    int current = destination;

    while (current != result->source) {
        if (count >= result->numVertices || count >= pathCapacity) {
            return -1;
        }

        path[count++] = current;
        current = result->prev[current];

        /* Broken predecessor chain: fail safely instead of looping. */
        if (current < 0 || current >= result->numVertices) {
            return -1;
        }
    }

    if (count >= pathCapacity) {
        return -1;
    }
    path[count++] = result->source;

    /* Reverse to obtain source -> destination order. */
    for (int left = 0, right = count - 1; left < right; left++, right--) {
        int temp = path[left];
        path[left] = path[right];
        path[right] = temp;
    }

    return count;
}

void freeDijkstraResult(DijkstraResult *result) {
    if (result == NULL) {
        return;
    }

    free(result->dist);
    free(result->prev);
    free(result);
}
