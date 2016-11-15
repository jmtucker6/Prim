#include "linkedlist.h"
#include "node.h"
#include "vertex.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

static void appendToList(LinkedList *, Node *);
static void removeNodeFromList(LinkedList *, Node *);
static bool isOneMemberInList(LinkedList *);
static void setHeadofList(LinkedList *, Node *);

LinkedList *newLinkedList(void) {
    LinkedList *list = malloc(sizeof(LinkedList));
    list -> head = NULL;
    list -> size = 0;
    return list;
};

void insertNode(LinkedList *list, Node *node) {
    if (isEmptyList(list)) {
        setHeadofList(list, node);
        setNextofNode(node, node);
        setPrevofNode(node, node);
    } else {
        appendToList(list, node);
    }
    list -> size++;
};


void deleteNode(LinkedList *list, Node *node) {
    if (isEmptyList(list))
        return;
    if (isOneMemberInList(list)) {
        setHeadofList(list, NULL);
    } else {
        removeNodeFromList(list, node);
    }
    list -> size--;
};

LinkedList *mergeLists(LinkedList *leftList, LinkedList *rightList) {
    if (isEmptyList(leftList))
        return rightList;
    else if (isEmptyList(rightList))
        return leftList;
    else {
        Node *leftTail = leftList -> head -> prev;
        Node *rightTail = rightList -> head -> prev;
        setNextofNode(leftTail, rightList -> head);
        setPrevofNode(rightList -> head, leftTail);

        setNextofNode(rightTail, leftList -> head);
        setPrevofNode(leftList -> head, rightTail);
        leftList -> size = leftList -> size + rightList -> size;
    }
    return leftList;
};

void displayLinkedList(LinkedList *list) {
    Node *node = list -> head;
    printf("Linked List:");
    for (int i = 0; i < list -> size; i++) {
        Vertex *currVertex = (Vertex *) node -> vertex;
        Vertex *parentVertex = node -> parent ? node -> parent -> vertex : NULL;
        Vertex *nextVertex = (Vertex *) node -> next -> vertex;
        Vertex *prevVertex = (Vertex *) node -> prev -> vertex;
        printf(" %d(%d)[p:%d,n:%d,prev:%d]", currVertex -> id,
                currVertex -> key,
                parentVertex ? parentVertex-> id : -1,
                nextVertex -> id,
                prevVertex -> id);
        node = node -> next;
    }
    printf("\nSize: %d\n", list -> size);

}

static void appendToList(LinkedList *list, Node *node) {
        Node *tail = list -> head -> prev;
        setPrevofNode(node, tail);
        setNextofNode(tail, node);

        setNextofNode(node, list -> head);
        setPrevofNode(list -> head, node);
}

static void removeNodeFromList(LinkedList *list, Node *node) {
    Node *prev = node -> prev;
    Node *next = node -> next;
    setNextofNode(prev, next);
    setPrevofNode(next, prev);
    if (list -> head == node)
        setHeadofList(list, next);
}
static bool isOneMemberInList(LinkedList *list) {
    return (list -> size == 1) ? true : false;
}

bool isEmptyList(LinkedList *list) {
    return (list -> size == 0) ? true : false;
}

static void setHeadofList(LinkedList *list, Node *node) {
    list -> head = node;
};
