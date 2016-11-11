#ifndef _LINKEDLIST_H_
#define _LINKEDLIST_H_
#include "node.h"
#include <stdbool.h>

typedef struct LinkedList {
    Node *head;
    int size;
} LinkedList;

extern LinkedList *newLinkedList();
extern void insertNode(LinkedList *, Node *);
extern void deleteNode(LinkedList *, Node *);
extern LinkedList *mergeLists(LinkedList *, LinkedList *);
extern bool isEmptyList(LinkedList *);
extern void displayLinkedList(LinkedList *);
#endif
