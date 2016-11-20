#include <stdlib.h>
#include <limits.h>
#include "vertex.h"

Vertex *newVertex() {
    Vertex *vertex = malloc(sizeof(Vertex));
    vertex -> id = 0;
    vertex -> key = INT_MAX;
    vertex -> predecessor = NULL;
    vertex -> owner = NULL;
    return vertex;
}

Vertex *newVertexGivenId(int id) {
    Vertex *vertex = newVertex();
    setVertexId(vertex, id);
    return vertex;
};
Vertex *newKnownVertex(int id, int key) {
    Vertex *vertex = newVertexGivenId(id);
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
int vertexMinComparator(void *left, void *right) {
    Vertex *leftVertex = (Vertex *) left;
    Vertex *rightVertex = (Vertex *) right;
    if (leftVertex == NULL)
        return (rightVertex == NULL) ? 0 : -1;
    if (rightVertex == NULL)
        return 1;

    if (leftVertex -> key < rightVertex -> key) {
        return -1;
    } else if (leftVertex -> key > rightVertex -> key) {
        return 1;
    } else {
        if (leftVertex -> id < rightVertex -> id) {
            return -1;
        } else  if (leftVertex -> id > rightVertex -> id) {
            return 1;
        } else {
            return 0;
        }
    }
}
