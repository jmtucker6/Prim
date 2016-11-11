#include <stdlib.h>
#include "vertex.h"

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
