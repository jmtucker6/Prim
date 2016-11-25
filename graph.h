#include "vertex.h"
#include "edge.h"

typedef struct Graph {
    Vertex **vertices;
    int **edges;
    int maxIndex;
} Graph;

extern Graph *newGraph(int);
extern void setGraphUndirEdge(Graph *, Edge *);
extern void setGraphVertex(Graph *, Vertex *);
extern Graph *primMinSpanTree(Graph *);
extern void printMinForest(Graph *);
