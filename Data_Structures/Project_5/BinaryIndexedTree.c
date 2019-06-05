#include "BinaryIndexedTree.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define PRETTY_PRINT_BOUND 60

// "Private" functions ---------------------

Node * newNode()
{
    Node * newNode = (Node *) malloc(sizeof(Node));
    newNode->value = 69420;
    newNode->parent = NULL;
    newNode->right = NULL;
    newNode->left = NULL;
    return newNode;
}

Node * treePointerSearch(int value, BIT * tree)
{

}

void destroyTreeRecursion(Node * node)
{
    if(node == NULL)
        return;
    destroyTreeRecursion(node->right);
    destroyTreeRecursion(node->left);
    free(node);
}

void destroyTree(BIT * tree)
{
    destroyTreeRecursion(tree->root);
    tree->size = 0;
    tree->root = NULL;
}

Node * findMin(Node * current)
{
    if(current == NULL)
        return NULL;
    if(current->left == NULL)
        return current;
    else
        findMin(current->left);
}

Node * delete(int value, Node * node, BIT * tree) 
{
    Node * temp;

    if(node == NULL) 
        return NULL;

    if (value < node->value) 
        node->left = delete(value, node->left, tree);

    else if (value > node->value) 
        node->right = delete(value, node->right, tree);

    else if (node->left != NULL && node->right != NULL)
    {
        temp = findMin(node->right);
        node->value = temp->value;
        node->right = delete(node->value, node->right, tree);
    }
    else
    {
        temp = node;
        if (node->left == NULL)
            node = node->right;
        else if (node->right == NULL)
            node = node->left;
        free(temp);
        tree->size--;
    }
    return node;
}

int getTreeHeightRecursion(Node * node)
{
    if(node == NULL)
        return 0;
    int vLeft = getTreeHeightRecursion(node->left);
    int vRight = getTreeHeightRecursion(node->right);
    if(vRight > vLeft)
        return vRight + 1;
    else
        return vLeft + 1;
}

bool treeBalanced(Node * node) 
{ 
    if(node == NULL) 
        return 1;  
    
    int leftH = getTreeHeightRecursion(node->left); 
    int rightH = getTreeHeightRecursion(node->right); 
    
    int dif = leftH - rightH;
    if(dif < 0)
        dif = -dif;

    if(dif <= 1 && treeBalanced(node->left) && treeBalanced(node->right)) 
        return 1;

    return 0; 
} 

bool treeFullRecursion(Node * node)
{
    if (node == NULL) 
        return 1; 

    if (node->left == NULL && node->right == NULL) 
        return 1; 

    if (node->left != NULL && node->right != NULL) 
        return treeFullRecursion(node->left) && treeFullRecursion(node->right); 

    return 0; 
}

// "Public" functions --------------------

BIT * newTree()
{
    return (BIT *) malloc(sizeof(BIT));
}

void initilizeBIT(BIT * tree)
{
    tree->size = 0;
    tree->root = NULL;
}

bool loadTreeFromFile(char * fileName, BIT * tree)
{
    char folder[] = "./tree_files/";
    char * path = (char *) malloc(sizeof(folder) + sizeof(fileName) + 5);
    strcpy(path, folder);
    strcat(path, fileName);
    FILE * file = fopen(path, "r");
    int v = 0;
    if(file == NULL)
        return 0;
    destroyTree(tree);
    fscanf (file, "%d", &v);    
    while (!feof (file))
    {  
        treeInsert(v, tree);        
        fscanf (file, "%d", &v);      
    }
    fclose (file);
    return 1;
}


void treeInsert(int value, BIT * tree)
{
    if(tree->size == 0)
    {
        tree->root = newNode();
        tree->root->value = value;
        tree->size++;
        return;
    }
    tree->size++;
    Node * cNode = tree->root;
    Node * lastNode;
    while(cNode != NULL)
    {
        lastNode = cNode;
        if(cNode->value > value)
            cNode = cNode->left;
        else
            cNode = cNode->right;
    }
    cNode = newNode();
    cNode->value = value;
    if(lastNode != NULL)
    {
        cNode->parent = lastNode;
        if(lastNode->value > cNode->value)
            lastNode->left = cNode;
        else
            lastNode->right = cNode;
    }
}

bool treeSearch(int value, BIT * tree)
{
    Node * cNode = tree->root;
    while(cNode != NULL)
    {   
        if(cNode->value == value)
            return 1;
        else if(cNode->value > value)
            cNode = cNode->left;
        else
            cNode = cNode->right;
    }
    return 0;
}

void inOrderWalk(Node * node)
{
    if(node == NULL)
        return;
    inOrderWalk(node->left);
    printf("%d ", node->value);
    inOrderWalk(node->right);
}

void preOrderWalk(Node * node)
{
    if(node == NULL)
        return;
    printf("%d ", node->value);
    inOrderWalk(node->left);
    inOrderWalk(node->right);
}

void postOrderWalk(Node * node)
{
    if(node == NULL)
        return;
    inOrderWalk(node->left);
    inOrderWalk(node->right);
    printf("%d ", node->value);
}

void recursiveFillMap(int height, int distance, char map[PRETTY_PRINT_BOUND][PRETTY_PRINT_BOUND], Node * node)
{
    if(node == NULL)
        return;
    map[height][PRETTY_PRINT_BOUND / 2 - distance * height] = '*';
    printf("ON %d with distance %d and height %d\n", node->value, distance, height);
    recursiveFillMap(height + 1, distance * 2, map, node->left);
    recursiveFillMap(height + 1, distance * 2 + 1, map, node->right);
}

void showTree(BIT * tree)
{
    if(tree->size > 20)
        return;
    char map[PRETTY_PRINT_BOUND][PRETTY_PRINT_BOUND];

    for(int i = 0; i < PRETTY_PRINT_BOUND; i++)
        for(int j = 0; j < PRETTY_PRINT_BOUND ; j++)
            map[i][j] = ' ';

    recursiveFillMap(0, 1, map, tree->root);
    
    for(int i = 0; i < 10; i++)
    {
        for(int j = 0; j < PRETTY_PRINT_BOUND; j++)
            printf("%c", map[i][j]);
        printf("\n");
    }
    
}

bool removeFromTree(int value, BIT * tree)
{
    int treeSizeBefore = tree->size;

    delete(value, tree->root, tree);

    if(treeSizeBefore != tree->size)
        return 1;
    else
        return 0;
}

bool treeFull(BIT * tree)
{
    return treeFullRecursion(tree->root);
}

int getTreeHeight(BIT * tree)
{
    return getTreeHeightRecursion(tree->root);
}

bool balanceTree(BIT * tree)
{
    if(treeBalanced(tree->root))
        return 0;
    
}
/*
int main()
{
    BIT tree;
    initilizeBIT(&tree);
    treeInsert(2, &tree);
    treeInsert(1, &tree);
    treeInsert(3, &tree);
    printf("HEIGHT: %d\n", getTreeHeight(&tree));
    printf("BALANCED: %s\n", treeBalanced(tree.root) ? "BALANCED" : "NOT BALANCED");
    printf("TREE FULL: %s\n", treeFull(&tree) ? "FULL" : "NOT FULL");
}
*/