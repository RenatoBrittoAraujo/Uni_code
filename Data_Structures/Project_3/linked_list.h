#ifndef LINKED_LIST
#define LINKED_LIST

#include "person.h"

struct Node
{
    Person * person;
    struct Node * next;
};

typedef struct Node Node;

struct LinkedList
{
    Node * root;
    Node * end;
    int size;
    bool sorted;
};

typedef struct LinkedList LinkedList;

LinkedList * newLinkedList();
void destroyLinkedList(LinkedList * list);
void addToLinkedList(Person * person, LinkedList * list);
void sortAddToLinkedList(Person * person, LinkedList * list);
void removeFromLinkedList(Node * node, LinkedList * list);
void sortList(LinkedList * list);
void next(Node ** current_node);
Node * getFirstNameInstance(char * name, LinkedList * list);
void listIteration(LinkedList * list);
int stringCompare(const char * a, const char * b);

#endif