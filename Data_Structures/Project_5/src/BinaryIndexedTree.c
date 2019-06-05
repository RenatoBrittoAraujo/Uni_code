#include "BinaryIndexedTree.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// Funções "Privadas"

Node * newNode()
{
    Node * newNode = (Node *) malloc(sizeof(Node));
    newNode->value = 69420;
    newNode->parent = NULL;
    newNode->right = NULL;
    newNode->left = NULL;
    return newNode;
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

Node * findMin(Node * node)
{
    if(node == NULL)
        return NULL;
    if(node->left == NULL)
        return node;
    else
        return findMin(node->left);
}

Node * findMax(Node * node)
{
    if(node == NULL)
        return NULL;
    if(node->right == NULL)
        return node;
    else 
        return findMax(node->right);
}

Node * deleteValue(int value, Node * node, BIT * tree) 
{
    Node * temp;

    if(node == NULL) 
        return NULL;

    if (value < node->value) 
        node->left = deleteValue(value, node->left, tree);

    else if (value > node->value) 
        node->right = deleteValue(value, node->right, tree);

    else if (node->left != NULL && node->right != NULL)
    {
        temp = findMin(node->right);
        node->value = temp->value;
        node->right = deleteValue(node->value, node->right, tree);
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
        return treeFullRecursion(node->left) && treeFullRecursion(node->right) && getTreeHeightRecursion(node->left) == getTreeHeightRecursion(node->right); 

    return 0; 
}

void treeToBackBone(Node * node, BIT * tree, bool left)
{
    if(node == NULL)
        return;

    treeToBackBone(node->right, tree, 0);

    if(node->left != NULL)
        treeToBackBone(node->left, tree, 1);
    else
        return;

    Node * child = node->left;

    if(node->parent == NULL)
    {
        tree->root = child;
        child->parent = NULL;
    }
    else if(left)
    {
        node->parent->left = child;
        child->parent = node->parent;
    }
    else if(!left)
    {
        node->parent->right = child;
        child->parent = node->parent;
    }

    Node * last = findMax(child);
    last->right = node;
    node->parent = last;
    node->left = NULL;
}

void backBoneToTree(Node * node, BIT * tree)
{
    if(node == NULL)
        return;
    Node * child = node->right;
    if(child == NULL || child->right == NULL)
        return;
    if(node->parent == NULL)
    {
        child->parent = NULL;
        tree->root = child;
    }
    else
    {
        node->parent->right = child;
        child->parent = node->parent;
    }
    Node * last = findMax(node);
    node->parent = child;
    node->right = child->left;
    child->left = node;
    backBoneToTree(child->right, tree);
}

void saveTreeRecursion(Node * node, FILE * file)
{
    if(node == NULL)
        return;
    fprintf(file, "%d ", node->value);
    saveTreeRecursion(node->left, file);
    saveTreeRecursion(node->right, file);
}

// Funções "Publicas"

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

    do
    {  
        fscanf (file, "%d", &v); 
        treeInsert(v, tree);        
    } while (!feof (file));

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
    preOrderWalk(node->left);
    preOrderWalk(node->right);
}

void postOrderWalk(Node * node)
{
    if(node == NULL)
        return;
    postOrderWalk(node->left);
    postOrderWalk(node->right);
    printf("%d ", node->value);
}

bool removeFromTree(int value, BIT * tree)
{
    int treeSizeBefore = tree->size;

    deleteValue(value, tree->root, tree);

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
    int height = getTreeHeightRecursion(tree->root) - 1;
    return height >= 0 ? height : 0;
}

bool balanceTree(BIT * tree)
{
    if(treeBalanced(tree->root))
        return 0;
    treeToBackBone(tree->root, tree, 0);
    int repetitions = -1;
    int size = tree->size;
    while(size / 2 > 0)
    {
        size /= 2;
        repetitions++;
    }
    for(int i = 0; i < repetitions; i++)
        backBoneToTree(tree->root, tree);
    return 1;
}

void clearTree(BIT * tree)
{
    destroyTree(tree);
}

void saveTree(char * name, BIT * tree)
{
    char folder[] = "./tree_files/";
    char * path = (char *) malloc(sizeof(folder) + sizeof(name) + 5);
    strcpy(path, folder);
    strcat(path, name);
    FILE * file = fopen(path, "a");
    if(file == NULL)
        return;
    saveTreeRecursion(tree->root, file);
    fclose(file);
}