#ifndef _BINOMIALHEAP_H_
#define _BINOMIALHEAP_H_

#include "node.h"
#include "linkedlist.h"

typedef struct BinomialHeap {
    Node *min;
    int (*comparator) (void *, void *);
    LinkedList *rootList;
    int size;
} BinomialHeap;

extern BinomialHeap *newBinomialHeap(int (*)(void *, void*));
extern void combineBinomialHeaps(BinomialHeap *, BinomialHeap *);
extern Node *insertIntoHeap(BinomialHeap *, void *);
extern void decreaseKey(BinomialHeap *, Node *, void *);
extern void deleteFromHeap(BinomialHeap *, Node *);
extern void *extractMin(BinomialHeap *);

#endif
