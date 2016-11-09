#ifndef _LINKEDLIST_H_
#define _LINKEDLIST_H_
#include "node.h"

typedef struct LinkedList {
    Node *head;
    int size;
} LinkedList;

extern LinkedList *newLinkedList();
extern void insertNode(LinkedList *, Node *);
extern void deleteNode(LinkedList *, Node *);
extern LinkedList *mergeLists(LinkedList *, LinkedList *);
#endif
