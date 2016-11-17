#ifndef _EDGE_H_
#define _EDGE_H_
typedef struct Edge {
    int sourceId;
    int sinkId;
    int weight;
} Edge;

extern Edge *newEdge(int, int, int);
#endif
