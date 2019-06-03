#include "queue.h"
#include <stdbool.h>
  
void initializeQueue(Queue * queue)
{
    queue->size = 0;
    queue->back = NULL;
}

void add(Flight * flight, Queue * queue)
{
    Node * newFlight = (Node *) malloc(sizeof(Node));
    newFlight->flight = flight;
    newFlight->last = queue->back;
    queue->back = newFlight;
    queue->size++;
}

Flight * front(Queue * queue)
{
    if(queue->back == NULL)
        return NULL;
    return queue->back->flight;
}

void pop(Queue * queue)
{
    if(queue->back == NULL)
        return;
    Node * toDestroy = queue->back;
    queue->back = queue->back->last;
    free(toDestroy);
    queue->size--;
}

bool empty(Queue * queue)
{
    return queue->size <= 0;
}

void destroyQueue(Queue * queue)
{
    Node * back = queue->back;
    while(back != NULL)
    {
        Node * newNode = back->last;
        free(back);
        back = newNode;
    }
    free(queue);
}