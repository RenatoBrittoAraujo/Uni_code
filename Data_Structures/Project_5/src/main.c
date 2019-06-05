#include <stdio.h>
#include "BinaryIndexedTree.h"
#include "TreePrinter.h"

#define mloadTree 1
#define mshowTree 2
#define mtreeFull 3
#define msearchTree 4
#define mgetHeight 5
#define mremoveTree 6
#define minOrder 7
#define mpreOrder 8
#define mpostOrder 9
#define mbalance 10
#define madd 11
#define mclear 12
#define msave 13

void showOptions()
{
    printf("Options:\n\n");
    printf("%d - Load tree from file\n", mloadTree);
    printf("%d - Show tree\n", mshowTree);
    printf("%d - Is tree full\n", mtreeFull);
    printf("%d - Search Value\n", msearchTree);
    printf("%d - Get tree height\n", mgetHeight);
    printf("%d - Remove value\n", mremoveTree);
    printf("%d - In-order walk\n", minOrder);
    printf("%d - Pre-order walk\n", mpreOrder);
    printf("%d - Post-order walk\n", mpostOrder);
    printf("%d - Balance tree\n", mbalance);
    printf("%d - Add to tree\n", madd);
    printf("%d - Clear tree\n", mclear);
    printf("%d - Save tree as file\n", msave);
    printf("0 - Exit\n");
}

BIT * tree;

void fLoadTree()
{
    printf("File name: ");
    char name[1000];
    scanf("%s", name);
    printf("\n");
    if(!loadTreeFromFile(name, tree))
        printf("Failed to find file");
    else
        printf("File loaded");
}

void fShowTree()
{
    if(tree->size == 0)
    {
        printf("Tree is empty");
        return;
    }
    if(tree->size > 20)
    {
        printf("Tree exceeds maximum size to be displayed");
        return;
    }
    adaptAndPrint(tree);
}

void fTreeFull()
{
    printf("Tree is %s", treeFull(tree) ? "full" : "not full");
}

void fSearchTree()
{
    int value;
    printf("Value to be searched: ");
    scanf("%d", &value);
    printf("\n%d was %s", value, treeSearch(value, tree) ? "found" : "not found");
}

void fGetHeight()
{
    printf("Tree height: %d", getTreeHeight(tree));
}

void fRemoveTree()
{
    printf("Value to be removed: ");
    int value;
    scanf("%d", &value);
    printf("\n%d was %s", value, removeFromTree(value, tree) ? "removed" : "not found");
}

void fInOrder()
{
    printf("In-order walk: ");
    inOrderWalk(tree->root);
}

void fPreOrder()
{
    printf("Pre-order walk: ");
    preOrderWalk(tree->root);
}

void fPostOrder()
{
    printf("Post-order walk: ");
    postOrderWalk(tree->root);
}

void fBalance()
{
    if(balanceTree(tree))
        printf("Tree was balaced");
    else
        printf("Tree is already balanced");
}

void fAdd()
{
    printf("Value to be added: ");
    int value;
    scanf("%d", &value);
    if(treeSearch(value, tree))
        printf("\nAlready on tree");
    else
    {
        treeInsert(value, tree);
        printf("\nAdded to tree");
    }
}

void fclear()
{
    printf("Tree was cleared");
    clearTree(tree);
}

void fsaveFile()
{
    if(tree->size == 0)
    {
        printf("Trying to save empty tree");
        return;
    }
    char name[100];
    printf("File name: ");
    scanf("%s", name);
    saveTree(name, tree);
    printf("\nFile was saved");
}

void system(char * operation);

int main()
{  
    tree = newTree();

    int selection;
    printf("Binary indexed trees :D\n\n");
    initilizeBIT(tree);

    while(1)
    {
        system("clear");
        showOptions();
        
        printf("\nSelection: ");
        scanf("%d", &selection);
        printf("\n");
        
        switch (selection)
        {
        case 0:
            return 0;
            break;
        case mloadTree:
            fLoadTree();
            break;
        case mshowTree:
            fShowTree();
            break;
        case mtreeFull:
            fTreeFull();
            break;
        case msearchTree:
            fSearchTree();
            break;
        case mgetHeight:
            fGetHeight();
            break;
        case mremoveTree:
            fRemoveTree();
            break;
        case minOrder:
            fInOrder();
            break;
        case mpreOrder:
            fPreOrder();
            break;
        case mpostOrder:
            fPostOrder();
            break;
        case mbalance:
            fBalance();
            break;     
        case madd:
            fAdd();
            break; 
        case mclear:
            fclear();
            break;
        case msave:
            fsaveFile();
            break;
        default:
            printf("Invalid option");
            break;
        }

    printf("\n\n");
    char random;
    printf("Press any key to continue: ");
    scanf(" %c", &random);
    }  

    return 0;
}