/*
 * queue.c
 *
 *  Created on: Mar 27, 2016
 *      Author: uidj2420
 */

#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

Queue* createQueue(int32_t maxElements)
{
        /* Create a Queue */
        Queue *Q;
        Q = (Queue*)malloc(sizeof(Queue));
        /* Initialise its properties */
        Q->element = (int*)malloc(sizeof(int)*maxElements);
        Q->size = 0;
        Q->capacity = maxElements;
        Q->front = 0;
        Q->rear = -1;
        /* Return the pointer */
        return Q;
}

void dequeue(Queue* Q)
{
        /* If Queue size is zero then it is empty. So we cannot pop */
        if(Q->size==0)
        {
                printf("Queue is Empty\n");
                return;
        }
        /* Removing an element is equivalent to incrementing index of front by one */
        else
        {
                Q->size--;
                Q->front++;
                /* As we fill elements in circular fashion */
                if(Q->front==Q->capacity)
                {
                        Q->front=0;
                }
        }
        return;
}

int32_t front(Queue* Q)
{
        if(Q->size==0)
        {
                printf("Queue is Empty\n");
                exit(0);
        }
        /* Return the element which is at the front*/
        return Q->element[Q->front];
}

void enqueue(Queue* Q, int32_t element)
{
        /* If the Queue is full, we cannot push an element into it as there is no space for it.*/
        if(Q->size == Q->capacity)
        {
                printf("Queue is Full\n");
        }
        else
        {
                Q->size++;
                Q->rear = Q->rear + 1;
                /* As we fill the queue in circular fashion */
                if(Q->rear == Q->capacity)
                {
                        Q->rear = 0;
                }
                /* Insert the element in its rear side */ 
                Q->element[Q->rear] = element;
        }
        return;
}
