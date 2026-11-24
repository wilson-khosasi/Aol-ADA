#include <limits.h>
#include <stdlib.h>

#include "dijkstra.h"
#include "priority_queue.h"

/*
 * Ordinary Dijkstra using the team's shared priority queue.
 *
 * The current priority_queue.h does not expose decreaseKey(). Therefore,
 * each improved distance is inserted as a new heap entry. Older entries
 * become stale and are skipped when extracted if their priority no longer
 * matches dist[vertex]. This approach requires insert() to support duplicate
 * vertex entries and the priority queue to grow dynamically.
 *
 * API return-value convention expected here:
 *   insert()      -> non-zero on success, zero on failure
 *   extractMin()  -> non-zero on success, zero if extraction fails
 */
DijkstraResult *dijkstra(const Graph *graph, int source) {
    if (graph == NULL || graph->vertices == NULL || graph->numVertices <= 0) {
        return NULL;
    }

    const int n = graph->numVertices;
    if (source < 0 || source >= n) {
        return NULL;
    }

    /* Validate all adjacency-list entries before starting the algorithm. */
    for (int u = 0; u < n; u++) {
        for (const Node *edge = graph->vertices[u].head;
             edge != NULL;
             edge = edge->next) {
            if (edge->dest < 0 || edge->dest >= n || edge->weight < 0) {
                return NULL;
            }
        }
    }

    DijkstraResult *result = malloc(sizeof(*result));
    if (result == NULL) {
        return NULL;
    }

    result->numVertices = n;
    result->source = source;
    result->dist = malloc((size_t)n * sizeof(*result->dist));
    result->prev = malloc((size_t)n * sizeof(*result->prev));

    if (result->dist == NULL || result->prev == NULL) {
        freeDijkstraResult(result);
        return NULL;
    }

    for (int v = 0; v < n; v++) {
        result->dist[v] = DIJKSTRA_INF;
        result->prev[v] = -1;
    }
    result->dist[source] = 0;

    /* Initial capacity is n; insert() is expected to grow the heap as needed. */
    priorityQueue *pq = createPriorityQueue(n);
    if (pq == NULL) {
        freeDijkstraResult(result);
        return NULL;
    }

    if (!insert(pq, source, 0)) {
        freePriorityQueue(pq);
        freeDijkstraResult(result);
        return NULL;
    }

    while (!isEmpty(pq)) {
        heapNode minNode;

        if (!extractMin(pq, &minNode)) {
            freePriorityQueue(pq);
            freeDijkstraResult(result);
            return NULL;
        }

        const int u = minNode.vertex;

        /* Guard against malformed queue entries. */
        if (u < 0 || u >= n) {
            freePriorityQueue(pq);
            freeDijkstraResult(result);
            return NULL;
        }

        /* Ignore outdated entries created before a later distance decrease. */
        if (minNode.priority != result->dist[u]) {
            continue;
        }

        /* Relax every outgoing edge from the extracted minimum vertex. */
        for (const Node *edge = graph->vertices[u].head;
             edge != NULL;
             edge = edge->next) {
            const int v = edge->dest;
            const int travelTime = edge->weight;

            /* Defensive validation in case graph memory was modified later. */
            if (v < 0 || v >= n || travelTime < 0) {
                freePriorityQueue(pq);
                freeDijkstraResult(result);
                return NULL;
            }

            /* Avoid signed integer overflow when adding edge weights. */
            if (result->dist[u] > INT_MAX - travelTime) {
                continue;
            }

            const int newDistance = result->dist[u] + travelTime;

            if (newDistance < result->dist[v]) {
                result->dist[v] = newDistance;
                result->prev[v] = u;

                /* Insert a new entry; any older entry for v becomes stale. */
                if (!insert(pq, v, newDistance)) {
                    freePriorityQueue(pq);
                    freeDijkstraResult(result);
                    return NULL;
                }
            }
        }
    }

    freePriorityQueue(pq);
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

    /* Collect destination -> source, then reverse the sequence. */
    int count = 0;
    int current = destination;

    while (current != result->source) {
        if (count >= result->numVertices || count >= pathCapacity) {
            return -1;
        }

        path[count++] = current;
        current = result->prev[current];

        /* Detect an invalid or broken predecessor chain safely. */
        if (current < 0 || current >= result->numVertices) {
            return -1;
        }
    }

    if (count >= pathCapacity) {
        return -1;
    }
    path[count++] = result->source;

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
