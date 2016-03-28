/*
 * queue.h
 *
 *  Created on: Mar 27, 2016
 *      Author: uidj2420
 */

#ifndef QUEUE_H_
#define QUEUE_H_

typedef struct Queue
{
        int capacity;
        int size;
        int front;
        int rear;
        int *element;
}Queue;

Queue* createQueue(int32_t maxElements);

void dequeue(Queue* Q);

int32_t front(Queue* Q);

void enqueue(Queue* Q, int32_t element);

#endif /* QUEUE_H_ */
