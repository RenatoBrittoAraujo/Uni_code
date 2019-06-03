#ifndef QUEUE
#define QUEUE

#include <stdlib.h>
#include <stdbool.h>

struct Flight
{
    int fuel;
    bool landing;
    char * flightNumber;
};

typedef struct Flight Flight;

struct Node
{
    Flight * flight;
    struct Node * last;
};

typedef struct Node Node;

struct Queue
{
    int size;
    Node * back;
};

typedef struct Queue Queue;

void initializeQueue(Queue * queue);
void add(Flight * flight, Queue * queue);
void pop(Queue * queue);
Flight * front(Queue * queue);
void destroyQueue(Queue * queue);

#endif