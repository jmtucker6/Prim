#include <stdlib.h>
#include <stdio.h>
#include "scanner.h"
#include "vertex.h"
#include "node.h"
#include "linkedlist.h"
#include "binomialheap.h"
#include "edge.h"


static Edge *readEdge(FILE *);
int main (void) {

    return 0;
}

static Edge *readEdge(FILE *fp) {
    int v1, v2, weight;
    v1 = readInt(fp);
    v2 = readInt(fp);
    char *temp = readToken(fp);
    if (*temp == ';') {
        weight = 0;
    } else {
        weight = atoi(temp);
        readToken(fp);
    }
    Edge *edge = newEdge(v1, v2, weight);
    return edge;
};
