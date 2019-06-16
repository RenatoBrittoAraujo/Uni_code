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

// As 10 funções pedidas

bool loadTreeFromFile(char * fileName, BIT * tree);
bool treeSearch(int value, BIT * tree);
void inOrderWalk(Node * node);
void preOrderWalk(Node * node);
void postOrderWalk(Node * node);
void showTree(BIT * tree);
bool removeFromTree(int value, BIT * tree);
bool treeFull(BIT * tree);
int getTreeHeight(BIT * tree);
bool balanceTree(BIT * tree);

// Funções adicionais

void treeInsert(int value, BIT * tree);
void clearTree(BIT * tree);
void saveTree(char * name, BIT * tree);

#endif