#include "graph.h"
#include "binomialheap.h"
#include <stdlib.h>

static bool shouldUpdateNeighborValues(Vertex *, int);

Graph *newGraph(int maxIndex) {
    Graph *graph = malloc(sizeof(Graph));
    graph -> maxIndex = maxIndex;
    int size = maxIndex + 1;
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
    if (graph -> edges[edge -> sourceId][edge -> sinkId] == 0) {
        graph -> edges[edge -> sourceId][edge -> sinkId] = edge -> weight;
        graph -> edges[edge -> sinkId][edge -> sourceId] = edge -> weight;
        setGraphVertex(graph, newVertexGivenId(edge -> sourceId));
        setGraphVertex(graph, newVertexGivenId(edge -> sinkId));
    }
};

void setGraphVertex(Graph *graph, Vertex *vertex) {
    if (graph -> vertices[vertex -> id] == NULL)
        graph -> vertices[vertex -> id] = vertex;
};

Graph *primMinSpanTree(Graph *graph) {
    BinomialHeap *heap = newBinomialHeap(&vertexMinComparator);
    Edge *edge = NULL;
    Vertex *vertex = NULL;
    Graph *minimumSpanningTree = newGraph(graph -> maxIndex);
    for (int i = 0; i <= graph -> maxIndex; i++) {
        if (graph -> vertices[i] != NULL) {
            insertIntoHeap(heap, graph -> vertices[i]);
            setGraphVertex(minimumSpanningTree, graph -> vertices[i]);
        }
    }
    Vertex *tempMinVertex = (Vertex *) heap -> min -> vertex;
    setVertexPredecessor(tempMinVertex, tempMinVertex);
    while (!isEmptyHeap(heap)) {
        vertex = extractMin(heap);
        setVertexKey(vertex, 0);
        edge = newEdge(vertex -> id, vertex -> predecessor -> id,
                graph -> edges[vertex -> id][vertex -> predecessor -> id]);
        setGraphUndirEdge(minimumSpanningTree, edge);
        for (int i = 0; i <= graph -> maxIndex; i++) {
            int weight = graph -> edges[vertex -> id][i];
            Vertex *neighborVertex = graph -> vertices[i];
            if (shouldUpdateNeighborValues(neighborVertex, weight)) {
                setVertexPredecessor(neighborVertex, vertex);
                setVertexKey(neighborVertex, weight);
                decreaseKey(heap, neighborVertex -> owner, neighborVertex);
            }
        }
    }
    return minimumSpanningTree;
}

static bool shouldUpdateNeighborValues(Vertex *neighborVertex, int edgeWeight) {
    return edgeWeight != 0 && edgeWeight < neighborVertex -> key;
};
