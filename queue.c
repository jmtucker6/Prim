#include "queue.h"
#include <stdlib.h>
#include <stdbool.h>

Queue *newQueue() {
    Queue *queue = malloc(sizeof(Queue));
    queue -> head = NULL;
    queue -> tail = NULL;
    queue -> count = 0;
    return queue;
};
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
Vertex *dequeue(Queue *queue) {
    Vertex *vertex = (Vertex *) queue -> head -> vertex;
    queue -> head = queue -> head -> next;
    queue -> count--;
    return vertex;
};

bool isEmptyQueue(Queue *queue) {
    return queue -> head == NULL;
}
