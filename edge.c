#include <stdlib.h>
#include "edge.h"

Edge *newEdge(int v1, int v2, int weight) {
    Edge *edge = malloc(sizeof(Edge));
    edge -> v1 = v1;
    edge -> v2 = v2;
    edge -> weight = weight;
    return edge;
}
