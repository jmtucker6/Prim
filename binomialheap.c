#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <math.h>
#include "binomialheap.h"
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

BinomialHeap *newBinomialHeap(int (*comparator)(void *, void*)) {
    BinomialHeap *heap = malloc(sizeof(BinomialHeap));
    heap -> comparator = comparator;
    heap -> rootList = newLinkedList();
    heap -> min = NULL;
    heap -> size = 0;
    return heap;
}

void combineBinomialHeaps(BinomialHeap *recipient, BinomialHeap *donor) {
    recipient -> rootList = mergeLists(recipient -> rootList, donor -> rootList);
    recipient -> size += donor -> size;
    cleanBinomialHeap(donor);
    consolidateBinomialHeap(recipient);
}

Node *insertIntoHeap(BinomialHeap *heap, void *v) {
    Node *node = newNode(v);
    setChildrenofNode(node, newLinkedList());
    setParentofNode(node, node);
    insertNode(heap -> rootList, node);
    heap -> size++;
    consolidateBinomialHeap(heap);
    return node;
}

Node *decreaseKey(BinomialHeap *heap, Node *node, void *vertex) {
    node -> vertex = vertex;
    Node *finalNode = bubbleUp(heap, node);
    if(isExtremeValue(heap, finalNode))
        heap -> min = finalNode;
    return finalNode;
};

void deleteFromHeap(BinomialHeap *heap, Node *node) {
    decreaseKey(heap, node, newKnownVertex(0,0));
    extractMin(heap);
};

void *extractMin(BinomialHeap *heap) {
    Node *minimum = heap -> min;
    deleteNode(heap -> rootList, minimum);
    heap -> rootList = mergeLists(heap -> rootList, minimum -> children);
    consolidateBinomialHeap(heap);
    heap -> size--;
    return minimum -> vertex;
};

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

static void cleanBinomialHeap(BinomialHeap *heap) {
    heap -> rootList = newLinkedList();
    heap -> size = 0;
    heap -> min = NULL;
}

static Node *bubbleUp(BinomialHeap *heap, Node *node) {
    if (heap -> comparator(node -> vertex, node -> parent -> vertex) < 0) {
        swapNodeValueWithParent(node);
        return bubbleUp(heap, node -> parent);
    } else
        return node;
}

static int calculateConsolidationArraySize(BinomialHeap *heap) {
    return logBase2(heap -> size) + 1;
};

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


static bool isExtremeValue(BinomialHeap *heap, Node *node) {
    return heap -> min == NULL || 
        heap -> comparator(node -> vertex, heap -> min -> vertex) < 0;
};

static int logBase2(int num) {
    int result = 0;
    while(num >>= 1)
        ++result;
    return result;
};
