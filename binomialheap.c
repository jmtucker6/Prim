#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "binomialheap.h"
#include "vertex.h"

static void consolidateBinomialHeap(BinomialHeap *);
static void cleanBinomialHeap(BinomialHeap *);
static void bubbleUp(BinomialHeap *, Node *);

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

void *extractMin(BinomialHeap *);

static void consolidateBinomialHeap(BinomialHeap *heap) {
    fprintf(stderr, "CONSOLIDATE NOT IMPLEMENTED\n");
};

static void cleanBinomialHeap(BinomialHeap *heap) {
    heap -> rootList = newLinkedList();
    heap -> size = 0;
    heap -> min = NULL;
}

static void bubbleUp(BinomialHeap *heap, Node *node) {
    fprintf(stderr, "BUBBLE UP NOT IMPLEMENTED\n");
}
