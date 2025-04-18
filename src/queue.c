#include "queue.h"

#include <stdio.h>
#include <stdlib.h>

void init_queue(Queue *q) {
    q->front = -1;
    q->rear = -1;
}

int isEmpty(Queue *q) { return q->front == -1; }

int isFull(Queue *q) { return q->rear == MAX - 1; }

void enqueue(Queue *q, double value) {
    if (isFull(q)) {
        printf("Queue is full!\n");
        return;
    }
    if (isEmpty(q)) {
        q->front = 0;
    }
    q->rear++;
    q->items[q->rear] = value;
}

double dequeue(Queue *q) {
    if (isEmpty(q)) {
        printf("Queue is empty!\n");
        return -1.0;
    }
    double item = q->items[q->front];
    q->front++;
    if (q->front > q->rear) {
        q->front = q->rear = -1;
    }
    return item;
}
