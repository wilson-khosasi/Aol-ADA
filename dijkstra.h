#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include <limits.h>
#include "graph.h"

#define DIJKSTRA_INF INT_MAX

typedef struct {
    int numVertices;
    int source;
    int *dist;  /* Minimum total travel time from source to each vertex. */
    int *prev;  /* Previous vertex on the reconstructed shortest path. */
} DijkstraResult;

/*
 * Runs Ordinary Dijkstra from source using the shared binary min-heap API
 * declared in priority_queue.h.
 *
 * Edge weights represent non-negative travel time (not distance or money).
 * Returns a newly allocated result, or NULL if the input is invalid or an
 * allocation / priority-queue operation fails. The caller must release the
 * result with freeDijkstraResult().
 */
DijkstraResult *dijkstra(const Graph *graph, int source);

/*
 * Reconstructs the source-to-destination path into path[].
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
