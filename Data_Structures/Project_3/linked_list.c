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

// Leia mais: https://catonmat.net/ascii-case-conversion-trick
char toLower(char c)
{
    if(c >= 65 && c <= 90)
    {
        return c ^ 32;
    }
    return c;
}

int stringCompare(const char * a, const char * b)
{
    size_t comparison_size = strlen(a);
    if(strlen(b) < comparison_size)
        comparison_size = strlen(b);
    for(size_t i = 0; i < comparison_size; i++)
    {
        if(toLower(a[i]) < toLower(b[i]))
            return -1;
        if(toLower(a[i]) > toLower(b[i]))
            return 1;
    }
    if(strlen(a) < strlen(b))
        return -1;
    if(strlen(b) < strlen(a))
        return 1;

    return 0;
}

bool compareNodes(Node * a, Node * b)
{
    return stringCompare(a->person->name, b->person->name) > 0;
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
    Node * current_node = list->root;
    Node * newnode = newNode();
    newnode->person = person;
    if(list->root == NULL)
    {
        list->root = newnode;
        list->end = newnode;
        list->size = 1;
        return;
    }
    list->size = list->size + 1;

    Node * last = NULL;

    while(compareNodes(newnode, current_node))
    {
        last = current_node;
        next(&current_node);
        if(current_node == NULL)
            break;
    }

    if(last == NULL)
    {
        newnode->next = list->root;
        list->root = newnode;
    }
    else
    {
        newnode->next = current_node;
        last->next = newnode;
    }
}

void removeFromLinkedList(Node * node, LinkedList * list)
{
    Node * current_node = list->root;
    Node * last_node = NULL;
    while(current_node != NULL)
    {
        if(current_node == node)
            break;
        last_node = current_node;
        next(&current_node);
    }
    
    if(current_node == NULL)
        return;

    list->size = list->size - 1;

    if(last_node == NULL)
    {
        list->root = current_node->next;
        destroyNode(current_node);
        return;
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

    while(current_node != NULL && stringCompare(name, current_node->person->name))
        next(&current_node);

    if(current_node != NULL)
        return current_node;

    return NULL;
}
