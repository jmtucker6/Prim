#include <stdlib.h>
#include "edge.h"

/**
 * edge.c - implementation of edge object
 *
 * Written by Jacob M. Tucker
 */

/**
 * Edge constructor
 */
Edge *newEdge(int sourceId, int sinkId, int weight) {
    Edge *edge = malloc(sizeof(Edge));
    edge -> sourceId = sourceId;
    edge -> sinkId = sinkId;
    edge -> weight = weight;
    return edge;
}
