#include <stdlib.h>
#include "vertex.h"

Vertex *newVertex() {
    Vertex *vertex = malloc(sizeof(Vertex));
    vertex -> id = 0;
    vertex -> key = 0;
    vertex -> predecessor = NULL;
    vertex -> owner = NULL;
    return vertex;
}

Vertex *newKnownVertex(int id, int key) {
    Vertex *vertex = newVertex();
    setVertexId(vertex, id);
    setVertexKey(vertex, key);
    return vertex;
};

void setVertexId(Vertex *vertex, int id) {
    vertex -> id = id;
}
void setVertexKey(Vertex *vertex, int key) {
    vertex -> key = key;
}
void setVertexPredecessor(Vertex *vertex, Vertex* predecessor) {
    vertex -> predecessor = predecessor;
}
void setVertexOwner(Vertex *vertex, Node* owner) {
    vertex -> owner = owner;
}
int vertexMinComparator(Vertex *left, Vertex *right) {
    if (left -> key < right -> key) {
        return -1;
    } else if (left -> key > right -> key) {
        return 1;
    } else {
        if (left -> id < right -> id) {
            return -1;
        } else  if (left -> id > right -> id) {
            return 1;
        } else {
            return 0;
        }
    }
}
