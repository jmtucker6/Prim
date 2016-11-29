#ifndef _BINHEAP_H_
#define _BINHEAP_H_

#include "node.h"
#include "linkedlist.h"

typedef struct BinomialHeap {
    Node *min;
    int (*comparator) (void *, void *);
    LinkedList *rootList;
    int size;
} BinomialHeap;

extern BinomialHeap *newBinHeap(int (*)(void *, void*));
extern void combineBinomialHeaps(BinomialHeap *, BinomialHeap *);
extern Node *insertBinHeap(BinomialHeap *, void *);
extern Node *decreaseKeyBinHeap(BinomialHeap *, Node *, void *);
extern void deleteFromHeap(BinomialHeap *, Node *);
extern void *extractBinHeap(BinomialHeap *);
extern bool isEmptyHeap(BinomialHeap *);

#endif
