#ifndef _EDGE_H_
#define _EDGE_H_
typedef struct Edge {
    int v1;
    int v2;
    int weight;
} Edge;

extern Edge *newEdge(int, int, int);
#endif
