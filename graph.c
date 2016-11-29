#include "graph.h"
#include "binheap.h"
#include "queue.h"
#include <stdlib.h>
#include <limits.h>
#include <stdio.h>

static bool shouldUpdateNeighborValues(Vertex *, int);
static int getCount(Graph *);
static void printLevel(Graph *, Queue *);
static void printVertex(Graph *, Vertex *);
static void enqueueChildren(Queue *, Graph *, Vertex *);
static Vertex *getRootVertex(Graph *);
static void enqueueRootVertex(Queue *, Graph *);

Graph *newGraph(int maxIndex) {
    Graph *graph = malloc(sizeof(Graph));
    graph -> maxIndex = maxIndex;
    int size = maxIndex + 1;
    graph -> vertices = calloc(size, sizeof(Vertex *));
    graph -> edges = calloc(size, sizeof(int *));
    for (int i = 0; i < size; i++) {
        graph -> edges[i] = calloc(size, sizeof(int));
    }
    return graph;
};

void setGraphUndirEdge(Graph *graph, Edge *edge) {
    if (graph -> edges[edge -> sourceId][edge -> sinkId] == 0) {
        if (edge -> sourceId != edge -> sinkId) {
            graph -> edges[edge -> sourceId][edge -> sinkId] = edge -> weight;
            graph -> edges[edge -> sinkId][edge -> sourceId] = edge -> weight;
            setGraphVertex(graph, newVertexGivenId(edge -> sourceId));
        }
        setGraphVertex(graph, newVertexGivenId(edge -> sinkId));
    }
};

void setGraphVertex(Graph *graph, Vertex *vertex) {
    if (graph -> vertices[vertex -> id] == NULL)
        graph -> vertices[vertex -> id] = vertex;
};

Graph *primMinSpanTree(Graph *graph) {
    BinomialHeap *heap = newBinHeap(&vertexMinComparator);
    Edge *edge = NULL;
    Vertex *vertex = NULL;
    Graph *minimumSpanningTree = newGraph(graph -> maxIndex);
    for (int i = 0; i <= graph -> maxIndex; i++) {
        if (graph -> vertices[i] != NULL) {
            insertBinHeap(heap, graph -> vertices[i]);
            setGraphVertex(minimumSpanningTree, graph -> vertices[i]);
        }
    }
    while (!isEmptyHeap(heap)) {
        vertex = extractBinHeap(heap);
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
                decreaseKeyBinHeap(heap, neighborVertex -> owner, neighborVertex);
            }
        }
    }
    return minimumSpanningTree;
}

void printMinForest(Graph *minGraph) {
    Queue *queue = newQueue();
    Queue *levelQueue = newQueue();
    int count = getCount(minGraph);
    int currLevel = -1;
    int weight = 0;

    int firstVertexId = getRootVertex(minGraph) -> id;

    enqueueRootVertex(queue, minGraph);

    while (count > 0) {
        Vertex *currVertex = dequeue(queue);
        minGraph -> vertices[currVertex -> id] = NULL;
        if (currVertex -> predecessor == currVertex) {
            printLevel(minGraph, levelQueue);
            if (currVertex -> id != firstVertexId) {
                printf(";\nweight: %d\n", weight);
                weight = 0;
            }
            currLevel = -1;
        }
        weight += minGraph -> edges[currVertex -> predecessor -> id][currVertex -> id];
        if (currVertex -> key > currLevel) {
            printLevel(minGraph, levelQueue);
            currLevel++;
            if (currLevel == 0)
                printf("0 :");
            else
                printf(";\n%d :", currLevel);
        }
        enqueue(levelQueue, currVertex);
        //printVertex(minGraph, currVertex);
        enqueueChildren(queue, minGraph, currVertex);
        count--;
        if (isEmptyQueue(queue) && count > 0) {
            enqueueRootVertex(queue, minGraph);
        }
    }
    printLevel(minGraph, levelQueue);
    printf(";\nweight: %d\n", weight);
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

static void printLevel(Graph *graph, Queue *levelQueue) {
    if (levelQueue -> count == 0)
        return;
    Vertex **levelArray = calloc(levelQueue -> count, sizeof(Vertex *));
    int i = 0;
    while (!isEmptyQueue(levelQueue)) {
        levelArray[i] = dequeue(levelQueue);
        i++;
    }

    int maxIndex = i;
    int minIndex;
    for (int j = 0; j < maxIndex; j++) {
        minIndex = j;
        for (int k = j + 1; k < maxIndex; k++) {
            if (levelArray[k] -> id < levelArray[minIndex] -> id)
                minIndex = k;
        }

        if (levelArray[j] != levelArray[minIndex]) {
            Vertex *temp = levelArray[j];
            levelArray[j] = levelArray[minIndex];
            levelArray[minIndex] = temp;
        }
    }

    for (int i = 0; i < maxIndex - 1; i++) {
        printVertex(graph, levelArray[i]);
        printf(",");
    }
    printVertex(graph, levelArray[maxIndex - 1]);

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

static Vertex *getRootVertex(Graph *minGraph) {
    for (int i = 0; i <= minGraph -> maxIndex; i++) {
        if (minGraph -> vertices[i] != NULL)
            return minGraph -> vertices[i];
    }
    return NULL;
}

static void enqueueRootVertex(Queue *queue, Graph *minGraph) {
    enqueue(queue, getRootVertex(minGraph));
}
 
