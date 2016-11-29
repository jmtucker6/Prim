#include "node.h"
#include "vertex.h"
#include <stdbool.h>

typedef struct Queue {
    Node *head;
    Node *tail;
    int count;
} Queue;

extern Queue *newQueue();
extern void enqueue(Queue *, Vertex *);
extern Vertex *dequeue(Queue *);
extern bool isEmptyQueue(Queue *);
