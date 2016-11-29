#include <stdlib.h>
#include <limits.h>
#include "vertex.h"

/**
 * vertex.c - implementation of vertex object
 *
 * Written by Jacob M. Tucker
 */

/**
 * Returns a new vertex with initialized values
 */
Vertex *newVertex() {
    Vertex *vertex = malloc(sizeof(Vertex));
    vertex -> id = 0;
    vertex -> key = INT_MAX;
    vertex -> predecessor = NULL;
    vertex -> owner = NULL;
    return vertex;
}

/**
 * Returns a new vertex with given id
 */
Vertex *newVertexGivenId(int id) {
    Vertex *vertex = newVertex();
    setVertexId(vertex, id);
    return vertex;
};

/**
 * Returns a new vertex with given ID and key
 */
Vertex *newKnownVertex(int id, int key) {
    Vertex *vertex = newVertexGivenId(id);
    setVertexKey(vertex, key);
    return vertex;
};

/**
 * Changes value of vertex id
 */
void setVertexId(Vertex *vertex, int id) {
    vertex -> id = id;
}

/**
 * Changes value of vertex key
 */
void setVertexKey(Vertex *vertex, int key) {
    vertex -> key = key;
}

/**
 * Changes value of vertex predecessor pointer
 */
void setVertexPredecessor(Vertex *vertex, Vertex* predecessor) {
    vertex -> predecessor = predecessor;
}

/**
 * Changes value of vertex owner pointer
 */
void setVertexOwner(Vertex *vertex, Node* owner) {
    vertex -> owner = owner;
}

/**
 * Returns -1 if left is smaller, 0 if equal, 1 if right is smaller
 */
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
