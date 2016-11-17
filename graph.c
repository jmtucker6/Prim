#include "graph.h"
#include <stdlib.h>

Graph *newGraph(int size) {
    size = size + 1;
    Graph *graph = malloc(sizeof(Graph));
    graph -> vertices = malloc(sizeof(Vertex *) * size);
    graph -> edges = malloc(sizeof(int *) * size);
    for (int i = 0; i < size; i++) {
        graph -> edges[i] = malloc(sizeof(int) * size);
        graph -> vertices[i] = NULL;
        for (int j = 0; j < size; j++) {
            graph -> edges[i][j] = 0;
        }
    }
    return graph;
};

void setGraphUndirEdge(Graph *graph, Edge *edge) {
    if (graph -> edges[edge -> sourceId][edge -> sinkId] != 0) {
        graph -> edges[edge -> sourceId][edge -> sinkId] = edge -> weight;
        graph -> edges[edge -> sinkId][edge -> sourceId] = edge -> weight;
    }
};

void setGraphVertex(Graph *graph, Vertex *vertex) {
    graph -> vertices[vertex -> id] = vertex;
};

