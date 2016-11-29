#include <stdlib.h>
#include "node.h"
#include "linkedlist.h"
#include "vertex.h"

Node *newNode(void *vertex) {
    Node *node = malloc(sizeof(Node));
    if (node == NULL)
        // FATAL
        ;
   Vertex *v = (Vertex *) vertex; 
   v -> owner = node;
   node -> vertex = v;
   node -> next = NULL;
   node -> prev = NULL;
   node -> parent = NULL;
   node -> children = newLinkedList();
   return node;
};

void setParentofNode(Node *node, Node *parent) {
    node -> parent = parent;
};

void setNextofNode(Node *node, Node *next) {
    node -> next = next;
};

void setPrevofNode(Node *node, Node *prev) {
    node -> prev = prev;
};

void setChildrenofNode(Node *node, LinkedList *childList) {
    node -> children = childList;
};

void swapNodeValueWithParent(Node *node) {
    Vertex *swapVertex = (Vertex *) node -> vertex;
    node -> vertex = node -> parent -> vertex;
    node -> parent -> vertex = swapVertex;
    
    ((Vertex *) node -> vertex) -> owner = node;
    if (node -> parent -> vertex)
        ((Vertex *) node -> parent -> vertex) -> owner = node -> parent;
};
