#include "graph.h"
#include "binomialheap.h"
#include "queue.h"
#include <stdlib.h>
#include <limits.h>
#include <stdio.h>

static bool shouldUpdateNeighborValues(Vertex *, int);
static int getCount(Graph *);
static void printVertex(Graph *, Vertex *);
static void enqueueChildren(Queue *, Graph *, Vertex *);
static void enqueueRootVertex(Queue *, Graph *);

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
    while (!isEmptyHeap(heap)) {
        vertex = extractMin(heap);
        if (vertex -> key == INT_MAX)
            setVertexPredecessor(vertex, vertex);
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

void printMinForest(Graph *minGraph) {
    Queue *queue = newQueue();
    int count = getCount(minGraph);
    int currLevel = -1;
    int weight = 0;

    enqueueRootVertex(queue, minGraph);

    while (count > 0) {
        Vertex *currVertex = dequeue(queue);
        minGraph -> vertices[currVertex -> id] = NULL;
        if (currVertex -> predecessor == currVertex) {
            if (weight != 0) {
                printf("\nWeight: %d\n", weight);
                weight = 0;
            }
            currLevel = -1;
        }
        weight += minGraph -> edges[currVertex -> predecessor -> id][currVertex -> id];
        if (currVertex -> key > currLevel) {
            currLevel++;
            if (currLevel == 0)
                printf("0:");
            else
                printf("\n%d:", currLevel);
        }
        printVertex(minGraph, currVertex);
        enqueueChildren(queue, minGraph, currVertex);
        count--;
        if (isEmptyQueue(queue) && count > 0) {
            enqueueRootVertex(queue, minGraph);
        }
    }
    printf("\nWeight: %d\n", weight);
}

static bool shouldUpdateNeighborValues(Vertex *neighborVertex, int edgeWeight) {
    return edgeWeight != 0 && edgeWeight < neighborVertex -> key;
}; 

static int getCount(Graph *graph) {
    int count = 0;
    for (int i = 0; i <= graph -> maxIndex; i++) {
        if (graph -> vertices[i] != NULL) {
            count++;
        }
    }
    return count;
}

static void printVertex(Graph *graph, Vertex *vertex) {
    if (vertex -> predecessor == vertex) {
        printf(" %d", vertex -> id);
        return;
    }
    printf(" %d(%d)%d", vertex -> id, vertex -> predecessor -> id,
            graph -> edges[vertex -> id][vertex -> predecessor -> id]);

}

static void enqueueChildren(Queue *queue, Graph *graph, Vertex* vertex) {
    int currVertexId = vertex -> id;
    for (int i = 0; i <= graph -> maxIndex; i++) {
        Vertex *potentialChild = graph -> vertices[i];
        if (i != currVertexId && graph -> edges[currVertexId][i] != 0 && potentialChild != NULL && potentialChild -> predecessor == vertex) {
            setVertexKey(potentialChild, potentialChild -> predecessor -> key + 1);
            enqueue(queue, potentialChild);
        }
    }
}

static void enqueueRootVertex(Queue *queue, Graph *minGraph) {
    for (int i = 0; i <= minGraph -> maxIndex; i++) {
        if (minGraph -> vertices[i] != NULL) {
            enqueue(queue, minGraph -> vertices[i]);
            return;;
        }
    }
}
