#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include <limits.h>

#include "graph.h"

/*
 * Dijkstra's Algorithm (temporary array-based implementation).
 *
 * The graph edge weight represents TRAVEL TIME, not distance or money.
 * Keep all edge weights non-negative. The current Graph module's addEdge()
 * already accepts only positive weights.
 *
 * This version deliberately does not depend on priority_queue.h because
 * the shared Priority Queue module is still being developed. Before final
 * integration, replace the linear minimum-vertex selection with the shared
 * binary min-heap API.
 */

#define DIJKSTRA_INF INT_MAX

typedef struct {
    int numVertices;
    int source;
    int *dist;  /* Minimum travel time from source to each vertex. */
    int *prev;  /* Previous vertex on the current shortest path. */
} DijkstraResult;

/*
 * Runs Dijkstra from source.
 * Returns a newly allocated result, or NULL if the input is invalid or
 * memory allocation fails. The caller must release it with
 * freeDijkstraResult().
 */
DijkstraResult *dijkstra(const Graph *graph, int source);

/*
 * Reconstructs the path from result->source to destination.
 * Writes vertex IDs into path in source-to-destination order.
 * Returns:
 *   > 0 : number of vertices written (a path exists)
 *     0 : destination is unreachable
 *    -1 : invalid arguments or path buffer is too small
 */
int reconstructPath(
    const DijkstraResult *result,
    int destination,
    int *path,
    int pathCapacity
);

/* Frees the result and its internally allocated arrays. */
void freeDijkstraResult(DijkstraResult *result);

#endif
