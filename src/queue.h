#ifndef QUEUE_H
#define QUEUE_H

#define MAX 100

typedef struct {
    double items[MAX];
    int front, rear;
} Queue;

void init_queue(Queue *q);
int isEmpty(Queue *q);
int isFull(Queue *q);
void enqueue(Queue *q, double value);
double dequeue(Queue *q);
double peek(Queue *q);
#endif