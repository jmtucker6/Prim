#ifndef _VERTEX_H_
#define _VERTEX_H_

#include "node.h"
typedef struct Vertex {
    int id;
    int key;
    struct Vertex *predecessor;
    Node *owner;
} Vertex;

extern Vertex *newVertex();
extern Vertex *newKnownVertex(int, int);
extern void setVertexId(Vertex *, int);
extern void setVertexKey(Vertex *, int);
extern void setVertexPredecessor(Vertex *, Vertex *);
extern void setVertexOwner(Vertex *, Node *);
extern int vertexMinComparator(void *, void *);
#endif
