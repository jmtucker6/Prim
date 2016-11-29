#include "queue.h"
#include <stdlib.h>
#include <stdbool.h>

/**
 * queue.c - implementation of basic queue data structure
 *
 * Written by Jacob M. Tucker
 */

/**
 * Queue constructor
 */
Queue *newQueue() {
    Queue *queue = malloc(sizeof(Queue));
    queue -> head = NULL;
    queue -> tail = NULL;
    queue -> count = 0;
    return queue;
};

/**
 * Enqueues a vertex into the queue
 */
void enqueue(Queue *queue, Vertex *vertex) {
    if (isEmptyQueue(queue)) {
        queue -> head = newNode(vertex);
        queue -> tail = queue -> head;
    } else {
        queue -> tail -> next = newNode(vertex);
        queue -> tail = queue -> tail -> next;
    }
    queue -> count++;
};

/**
 * Dequeues a vertex from the queue
 */
Vertex *dequeue(Queue *queue) {
    Vertex *vertex = (Vertex *) queue -> head -> vertex;
    queue -> head = queue -> head -> next;
    queue -> count--;
    return vertex;
};

/**
 * Returns true if there are no nodes in the queue
 */
bool isEmptyQueue(Queue *queue) {
    return queue -> head == NULL;
}
