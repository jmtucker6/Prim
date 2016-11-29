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

/**
 * linkedlist.c - Implementation of a circular double-linked list
 *
 * Written by Jacob M. Tucker
 */

/**
 * LinkedList constructor
 */
LinkedList *newLinkedList(void) {
    LinkedList *list = malloc(sizeof(LinkedList));
    if (list == NULL)
        fprintf(stderr, "Out of Memory: Cannot allocate list\n");
    list -> head = NULL;
    list -> size = 0;
    return list;
};

/**
 * Inserts a node to back of linkedlist
 */
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


/**
 * Deletes a node from the list
 */
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

/**
 * Combines two list to form one large list stored at the address of the leftList
 */
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

        rightList -> head = NULL;
        rightList -> size = 0;
    }
    return leftList;
};

/**
 * Prints out the linked list
 */
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

/**
 * Attaches node to the back of the list
 */
static void appendToList(LinkedList *list, Node *node) {
        Node *tail = list -> head -> prev;
        setPrevofNode(node, tail);
        setNextofNode(tail, node);

        setNextofNode(node, list -> head);
        setPrevofNode(list -> head, node);
}

/**
 * Splices out a node from the list
 */
static void removeNodeFromList(LinkedList *list, Node *node) {
    Node *prev = node -> prev;
    Node *next = node -> next;
    setNextofNode(prev, next);
    setPrevofNode(next, prev);
    if (list -> head == node)
        setHeadofList(list, next);
}

/**
 * Returns true if there is one member in the list
 */
static bool isOneMemberInList(LinkedList *list) {
    return (list -> size == 1) ? true : false;
}

/**
 * Returns true if the list has no nodes
 */
bool isEmptyList(LinkedList *list) {
    return (list -> size == 0) ? true : false;
}

/**
 * Changes the value of the head pointer of the list
 */
static void setHeadofList(LinkedList *list, Node *node) {
    list -> head = node;
};
