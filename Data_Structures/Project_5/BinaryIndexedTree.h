#ifndef BinaryIndexedTree
#define BinaryIndexedTree

#include <stdbool.h>

struct Node
{
    int value;
    struct Node * parent;
    struct Node * left;
    struct Node * right;
};

typedef struct Node Node;

struct BIT
{
    Node * root;
    int size;
};

typedef struct BIT BIT;

BIT * newTree();
void initilizeBIT(BIT * tree);


bool loadTreeFromFile(char * fileName, BIT * tree);
void treeInsert(int value, BIT * tree);
bool treeSearch(int value, BIT * tree);
void inOrderWalk(Node * node);
void preOrderWalk(Node * node);
void postOrderWalk(Node * node);
void showTree(BIT * tree);
bool removeFromTree(int value, BIT * tree);
bool treeFull(BIT * tree);
int getTreeHeight(BIT * tree);
bool balanceTree(BIT * tree);

#endif