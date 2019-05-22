#include <stdlib.h>
#include <stdio.h>
#include "person.h"
#include "linked_list.h"
#include <string.h>

LinkedList * newLinkedList()
{
    LinkedList * newlist = (LinkedList *)malloc(sizeof(LinkedList));
    newlist->size = 0;
    newlist->end = NULL;
    newlist->root = NULL;
    newlist->sorted = false;
    return newlist;
}

bool compareNodes(Node * a, Node * b)
{
    return strcmp(a->person->name, b->person->name) > 0;
}

void swapNodes(Node * a, Node * b)
{
    Person * tmp = a->person;
    a->person = b->person;
    b->person = tmp;
}

Node * newNode()
{
    Node * newnode = (Node *)malloc(sizeof(Node));
    newnode->person = NULL;
    newnode->next = NULL;
    return newnode;
}

void destroyNode(Node * node)
{
    if(node->person != NULL)
        destroyPerson(node->person);
    if(node != NULL)
        free(node);
    node = NULL;
}

void destroyLinkedList(LinkedList * list)
{
    Node * cnode = list->root; 
    while(cnode != NULL)
    {
        Node * nextnode = cnode->next;
        destroyNode(cnode);
        cnode = nextnode;
    }
    free(list);
}

void addToLinkedList(Person * person, LinkedList * list)
{
    Node * newnode = newNode();
    newnode->person = person;
    if(list->root != NULL)
        list->end->next = newnode;
    else
        list->root = newnode;
    
    list->end = newnode;
}

void sortAddToLinkedList(Person * person, LinkedList * list)
{
    if(!list->sorted)
        sortList(list);
    Node * current_node = list->root;
    Node * newnode = newNode();
    newnode->person = person;
    if(list->size == 0)
    {
        list->root = newnode;
        list->end = newnode;
        list->size = 1;
        return;
    }
    list->size = list->size + 1;

    if(!compareNodes(newnode, current_node))
    {
        newnode->next = list->root;
        list->root = newnode;
        return;
    }

    while(current_node->next != NULL && compareNodes(newnode, current_node))
        next(&current_node);

    Node * next_node = current_node->next;
    current_node->next = newnode;
    newnode->next = next_node;
    if(current_node->next == NULL)
        list->end = newnode;
}

bool removeFromLinkedList(char * name, LinkedList * list)
{
    bool found = false;
    Node * current_node = list->root;
    Node * last_node = NULL;
    while(current_node != NULL)
    {
        if(!strcmp(current_node->person->name, name))
        {
            found = true;
            break;
        } 
        last_node = current_node;
        next(&current_node);
    }
    
    if(!found)
        return false;
    
    list->size = list->size - 1;

    if(last_node == NULL)
    {
        list->root = current_node->next;
        destroyNode(current_node);
    }
    last_node->next = current_node->next;
    destroyNode(current_node);
}

void sortList(LinkedList * list)
{
    if(list->sorted)
        return;

    Node * i = list->root;

    while(i != NULL)
    {
        Node * j = i->next;

        while(j != NULL)
        {
            if(compareNodes(i, j))
            {
                swapNodes(i, j);
            }
            next(&j);
        }
        next(&i);
    }
    list->sorted = true;
}

void next(Node ** current_node)
{
    *current_node = (*current_node)->next;
}

void listIteration(LinkedList * list)
{
    Node * c = list->root;
    while(c != NULL)
    {
        printf("%s ", c->person->name);
        next(&c);
    }
    printf("\n");
}

Node * getFirstNameInstance(char * name, LinkedList * list)
{
    Node * current_node = list->root;

    while(current_node != NULL && strcmp(name, current_node->person->name))
        next(&current_node);

    if(current_node != NULL)
        return current_node;

    return NULL;
}
