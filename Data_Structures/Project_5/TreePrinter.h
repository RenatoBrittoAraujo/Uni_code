#ifndef TREE_PRINTER
#define TREE_PRINTER

struct Tree 
{
  struct Tree * left;
  struct Tree * right;
  int element;
};

typedef struct Tree Tree;

void adaptAndPrint(BIT * tree);

#endif