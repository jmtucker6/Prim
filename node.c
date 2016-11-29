#include <stdlib.h>
#include "node.h"
#include "linkedlist.h"
#include "vertex.h"

/**
 * node.c - Implementation of node objects used for heap and queue
 *
 * Written by Jacob M. Tucker
 */

/**
 * Creates new node with initialized values
 */
Node *newNode(void *vertex) {
    Node *node = malloc(sizeof(Node));
   Vertex *v = (Vertex *) vertex; 
   v -> owner = node;
   node -> vertex = v;
   node -> next = NULL;
   node -> prev = NULL;
   node -> parent = NULL;
   node -> children = newLinkedList();
   return node;
};

/**
 * Changes a node's parent value
 */
void setParentofNode(Node *node, Node *parent) {
    node -> parent = parent;
};

/**
 * Changes a node's next pointer
 */
void setNextofNode(Node *node, Node *next) {
    node -> next = next;
};

/**
 * Changes a node's previous pointer
 */
void setPrevofNode(Node *node, Node *prev) {
    node -> prev = prev;
};

/**
 * Changes a node's child list
 */
void setChildrenofNode(Node *node, LinkedList *childList) {
    node -> children = childList;
};

/**
 * Exchanges values of a node's data with its parent
 */
void swapNodeValueWithParent(Node *node) {
    Vertex *swapVertex = (Vertex *) node -> vertex;
    node -> vertex = node -> parent -> vertex;
    node -> parent -> vertex = swapVertex;
    
    ((Vertex *) node -> vertex) -> owner = node;
    if (node -> parent -> vertex)
        ((Vertex *) node -> parent -> vertex) -> owner = node -> parent;
};
