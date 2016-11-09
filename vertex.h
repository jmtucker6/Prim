#ifndef _VERTEX_H_
#define _VERTEX_H_

#include "node.h"
typedef struct Vertex {
    int id;
    int key;
    struct Vertex *predecessor;
    Node *owner;
} Vertex;
#endif
