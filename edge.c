#include <stdlib.h>
#include "edge.h"

Edge *newEdge(int sourceId, int sinkId, int weight) {
    Edge *edge = malloc(sizeof(Edge));
    edge -> sourceId = sourceId;
    edge -> sinkId = sinkId;
    edge -> weight = weight;
    return edge;
}
