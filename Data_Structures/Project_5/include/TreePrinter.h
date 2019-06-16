#ifndef TREE_PRINTER
#define TREE_PRINTER

struct Tree 
{
  struct Tree * left;
  struct Tree * right;
  int element;
};

typedef struct Tree Tree;

struct printNode
{
  struct printNode * left;
  struct printNode * right;

  int edge_length; 
    
  int height;      

  int lablen;
 
  int parent_dir;   
                         
  char label[11];  
};

typedef struct printNode printNode;

void adaptAndPrint(BIT * tree);

#endif