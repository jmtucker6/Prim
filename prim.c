#include <stdlib.h>
#include <stdio.h>
#include "scanner.h"
#include "vertex.h"
#include "node.h"
#include "linkedlist.h"
#include "binomialheap.h"
#include "graph.h"
#include "edge.h"


static Edge *readEdge(FILE *);
static int findMaxVertexID(FILE *);
static Graph *readGraph(FILE *, int);

int main (int argc, const char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Call must be \"prim <filename>\"\n");
    }
    FILE *fp = fopen(argv[1], "r");
    int max = 0;
    max = findMaxVertexID(fp);
    fclose(fp);

    fp = fopen(argv[1], "r");
    Graph *graph = readGraph(fp, max);
    fclose(fp);

    Graph *minGraph = primMinSpanTree(graph);
    printMinForest(minGraph);
    return 0;
}

static Edge *readEdge(FILE *fp) {
    int sourceId, sinkId, weight;
    char *temp = readToken(fp);
    if (temp == NULL)
        return NULL;
    sourceId = atoi(temp);
    sinkId = readInt(fp);
    temp = readToken(fp);
    if (*temp == ';') {
        weight = 1;
    } else {
        weight = atoi(temp);
        readToken(fp);
    }
    Edge *edge = newEdge(sourceId, sinkId, weight);
    return edge;
};

static int findMaxVertexID(FILE *fp) {
    int max = 0;
    Edge *edge = readEdge(fp);
    while (!feof(fp)) {
       if (edge == NULL)
           return max;
       if (edge -> sourceId > max)
          max = edge -> sourceId;
       if (edge -> sinkId > max)
          max = edge -> sinkId; 
       edge = readEdge(fp);
    }
    return max;
}

static Graph *readGraph(FILE *fp, int max) {
    Graph *graph = newGraph(max);
    Edge *edge = readEdge(fp);
    while (!feof(fp)) {
        if (edge == NULL)
            return graph;
        setGraphUndirEdge(graph, edge);
        edge = readEdge(fp);
    }
    return graph;
}
