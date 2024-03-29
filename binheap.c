#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <math.h>
#include "binheap.h"
#include "vertex.h"
#include "linkedlist.h"

static void consolidateBinomialHeap(BinomialHeap *);
static void cleanBinomialHeap(BinomialHeap *);
static Node *bubbleUp(BinomialHeap *, Node *);
static int calculateConsolidationArraySize(BinomialHeap *);
static void updateConsolidationArray(BinomialHeap *, Node **, Node *);
static Node *combineSubheaps(BinomialHeap *, Node *, Node *);
static bool isExtremeValue(BinomialHeap *, Node *);
static int logBase2(int);
static void resetParentsOfListNodes(LinkedList *);

/**
 * binheap.c - Implementation of a Binomial Heap priority queue
 *
 * Written by Jacob M. Tucker
 */

/**
 * Constructor for Binomail Heap
 */
BinomialHeap *newBinHeap(int (*comparator)(void *, void*)) {
    BinomialHeap *heap = malloc(sizeof(BinomialHeap));
    heap -> comparator = comparator;
    heap -> rootList = newLinkedList();
    heap -> min = NULL;
    heap -> size = 0;
    return heap;
}

/**
 * Merges two Binomial heaps into the address of the left binomial heap
 */
void combineBinomialHeaps(BinomialHeap *recipient, BinomialHeap *donor) {
    recipient -> rootList = mergeLists(recipient -> rootList, donor -> rootList);
    recipient -> size += donor -> size;
    cleanBinomialHeap(donor);
    consolidateBinomialHeap(recipient);
}

/**
 * Inserts a node into the binomial heap
 */
Node *insertBinHeap(BinomialHeap *heap, void *v) {
    Node *node = newNode(v);
    setParentofNode(node, node);
    insertNode(heap -> rootList, node);
    heap -> size++;
    consolidateBinomialHeap(heap);
    return node;
}

/**
 * Decreases the key of a node in the binomial heap and maintains order
 */
Node *decreaseKeyBinHeap(BinomialHeap *heap, Node *node, void *vertex) {
    node -> vertex = vertex;
    Node *finalNode = bubbleUp(heap, node);
    if(isExtremeValue(heap, finalNode))
        heap -> min = finalNode;
    return finalNode;
};

/**
 * Removes a node from the binomial heap
 */
void deleteFromHeap(BinomialHeap *heap, Node *node) {
    decreaseKeyBinHeap(heap, node, NULL);
    extractBinHeap(heap);
};

/**
 * Removes the minumum from the heap
 * Returns the data of removed node
 */
void *extractBinHeap(BinomialHeap *heap) {
    Node *minimum = heap -> min;
    deleteNode(heap -> rootList, minimum);
    resetParentsOfListNodes(minimum -> children);
    heap -> rootList = mergeLists(heap -> rootList, minimum -> children);
    consolidateBinomialHeap(heap);
    heap -> size--;
    return minimum -> vertex;
};

/**
 * Returns true if the heap has no nodes
 */
bool isEmptyHeap(BinomialHeap *heap) {
    return heap -> size == 0;
};

/**
 * Restores binomial heap structure
 */
static void consolidateBinomialHeap(BinomialHeap *heap) {
    int arraySize = calculateConsolidationArraySize(heap);
    Node **consolidationArray = (Node **) malloc(sizeof(Node *) * arraySize);
    for (int i = 0; i < arraySize; i++) {
        consolidationArray[i] = malloc(sizeof(Node));
        consolidationArray[i] = NULL;
    }
    while (!isEmptyList(heap -> rootList)) {
        Node *currNode = heap -> rootList -> head;
        deleteNode(heap -> rootList, currNode);
        updateConsolidationArray(heap, consolidationArray, currNode);
    }
    heap -> min = NULL;
    for (int i = 0; i < arraySize; i++) {
        if (consolidationArray[i] != NULL) {
            insertNode(heap -> rootList, consolidationArray[i]);
            if (isExtremeValue(heap, consolidationArray[i])) {
                heap -> min = consolidationArray[i];
            }
        }
    }
    free(consolidationArray);
};

/**
 * Resets properties of binomial heap to default
 */
static void cleanBinomialHeap(BinomialHeap *heap) {
    heap -> rootList = newLinkedList();
    heap -> size = 0;
    heap -> min = NULL;
}

/**
 * Bubbles a node up to preserve heap ordering
 */
static Node *bubbleUp(BinomialHeap *heap, Node *node) {
    if (heap -> comparator(node -> vertex, node -> parent -> vertex) < 0) {
        swapNodeValueWithParent(node);
        return bubbleUp(heap, node -> parent);
    } else
        return node;
}

/**
 * Returns the size of the consolidation array
 */
static int calculateConsolidationArraySize(BinomialHeap *heap) {
    return logBase2(heap -> size) + 1;
};

/**
 * Updates the consolidatoin array during restoration of heap structure
 */
static void updateConsolidationArray(BinomialHeap *heap,
        Node **consolidationArray, Node *currNode) {
    int degree = currNode -> children -> size;
    while (consolidationArray[degree] != NULL) {
        currNode = combineSubheaps(heap, currNode, consolidationArray[degree]);
        consolidationArray[degree] = NULL;
        degree++;
    }
    consolidationArray[degree] = currNode;
}

/**
 * Merges two subheaps
 */
static Node *combineSubheaps(BinomialHeap *heap, Node *currNode, Node *nodeFromArray) {
    if (heap -> comparator(currNode -> vertex, nodeFromArray -> vertex) < 0) {
        insertNode(currNode -> children, nodeFromArray);
        setParentofNode(nodeFromArray, currNode);
        return currNode;
    } else {
        insertNode(nodeFromArray -> children, currNode);
        setParentofNode(currNode, nodeFromArray);
        return nodeFromArray;
    }
};


/**
 * Returns true if node holds extreme value of the heap
 */
static bool isExtremeValue(BinomialHeap *heap, Node *node) {
    return heap -> min == NULL || 
        heap -> comparator(node -> vertex, heap -> min -> vertex) < 0;
};

/**
 * Calculates log base 2 of an integer
 */
static int logBase2(int num) {
    int result = 0;
    while(num >>= 1)
        ++result;
    return result;
};

/**
 * Sets parent pointers of all nodes in the list to defaults
 */
static void resetParentsOfListNodes(LinkedList *list) {
    Node *tempNode = list -> head;
    for (int i = 0; i < list -> size; i++) {
        setParentofNode(tempNode, tempNode);
        tempNode = tempNode -> next;
    }
}
