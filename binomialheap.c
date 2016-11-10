#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "binomialheap.h"
#include "vertex.h"

static void consolidateBinomialHeap(BinomialHeap *);
static void cleanBinomialHeap(BinomialHeap *);
static void bubbleUp(BinomialHeap *, Node *);
static int calculateConsolidationArraySize(BinomialHeap *);
static void updateConsolidationArray(Node **, Node *);

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
    setParentofNode(node, node);
    setChildrenofNode(node, newLinkedList());
    insertNode(heap -> rootList, node);
    heap -> size++;
    consolidateBinomialHeap(heap);
    return node;
}

void decreaseKey(BinomialHeap *heap, Node *node, void *vertex) {
    node -> vertex = vertex;
    bubbleUp(heap, node);
};

void deleteFromHeap(BinomialHeap *heap, Node *node) {
    decreaseKey(heap, node, NULL);
    extractMin(heap);
};

void *extractMin(BinomialHeap *heap) {
    Node *minimum = heap -> min;
    deleteNode(heap -> rootList, minimum);
    mergeLists(heap -> rootList, minimum -> children);
    consolidateBinomialHeap(heap);
    heap -> size--;
    return minimum -> vertex;
};

// TODO: Pull out into smaller functions
static void consolidateBinomialHeap(BinomialHeap *heap) {
    int arraySize = calculateConsolidationArraySize(heap);
    Node **consolidationArray = malloc(sizeof(Node *) * arraySize);
    for (int i = 0; i < arraySize; i++) {
        consolidationArray[i] = NULL;
    }
    while (!isEmptyList(heap -> rootList)) {
        Node *currNode = heap -> rootList -> head;
        deleteNode(heap -> rootList, currNode);
        updateConsolidationArray(consolidationArray, currNode);
    }
    heap -> min = NULL;
    for (int i = 0; i < arraySize; i++) {
        if (consolidationArray[i] != NULL) {
            insertNode(heap -> rootList, consolidationArray[i]);
            if (heap -> min == NULL || 
                    heap -> comparator(consolidationArray[i], heap -> min) < 0) {
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

static void bubbleUp(BinomialHeap *heap, Node *node) {
    fprintf(stderr, "BUBBLE UP NOT IMPLEMENTED\n");
}

static int calculateConsolidationArraySize(BinomialHeap *heap) {
    fprintf(stderr, "CALCULATE NOT IMPLEMENTED\n");
};
static void updateConsolidationArray(Node **consolidationArray, Node *currNode) {
    fprintf(stderr, "UPDATE NOT IMPLEMENTED\n");
}
