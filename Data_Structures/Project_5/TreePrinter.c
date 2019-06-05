#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "BinaryIndexedTree.h"
#include "TreePrinter.h"

Tree * destroy(Tree *t)
{
	if (t != NULL)
	{
	destroy(t->left);
	destroy(t->right);
	free(t);
	}

	return NULL;
}
               
Tree * insert(int value, Tree * t) 
{
	Tree * new_node;
	if (t == NULL) 
	{
	new_node = (Tree *) malloc (sizeof (Tree));
	if (new_node == NULL) 
	{
		return t;
	}

	new_node->element = value;

		new_node->left = new_node->right = NULL;
		return new_node;
	}

	if (value < t->element) 
	{
	t->left = insert(value, t->left);
	} 
	else if (value > t->element) 
	{
		t->right = insert(value, t->right);
	} 
	return t;
}

typedef struct asciinode_struct asciinode;

struct asciinode_struct
{
  asciinode * left, * right;

  int edge_length; 
    
  int height;      

  int lablen;
 
  int parent_dir;   
                         
  char label[11];  
};

#define MAX_HEIGHT 1000
int lprofile[MAX_HEIGHT];
int rprofile[MAX_HEIGHT];
#define INFINITY (1<<20)

int gap = 3;  

int print_next;    

int MIN (int X, int Y)  
{
	return ((X) < (Y)) ? (X) : (Y);
}

int MAX (int X, int Y)  
{
	return ((X) > (Y)) ? (X) : (Y);
}

asciinode * buildAsciiTreeRecursive(Tree * t) 
{
	asciinode * node;
	
	if (t == NULL) return NULL;

	node = malloc(sizeof(asciinode));
	node->left = buildAsciiTreeRecursive(t->left);
	node->right = buildAsciiTreeRecursive(t->right);
	
	if (node->left != NULL) 
	{
		node->left->parent_dir = -1;
	}

	if (node->right != NULL) 
	{
		node->right->parent_dir = 1;
	}

	sprintf(node->label, "%d", t->element);
	node->lablen = strlen(node->label);

	return node;
}

asciinode * buildAsciiTree(Tree * t) 
{
	asciinode *node;
	if (t == NULL) return NULL;
	node = buildAsciiTreeRecursive(t);
	node->parent_dir = 0;
	return node;
}

void destroyAsciiTree(asciinode *node) 
{
	if (node == NULL) return;
	destroyAsciiTree(node->left);
	destroyAsciiTree(node->right);
	free(node);
}

void leftProfile(asciinode *node, int x, int y) 
{
	int i, isleft;
	if (node == NULL) return;
	isleft = (node->parent_dir == -1);
	lprofile[y] = MIN(lprofile[y], x-((node->lablen-isleft)/2));
	if (node->left != NULL) 
	{
		for (i=1; i <= node->edge_length && y+i < MAX_HEIGHT; i++) 
	{
		lprofile[y+i] = MIN(lprofile[y+i], x-i);
	}
	}
	leftProfile(node->left, x-node->edge_length-1, y+node->edge_length+1);
	leftProfile(node->right, x+node->edge_length+1, y+node->edge_length+1);
}

void rightProfile(asciinode *node, int x, int y) 
{
	int i, notleft;
	if (node == NULL) return;
	notleft = (node->parent_dir != -1);
	rprofile[y] = MAX(rprofile[y], x+((node->lablen-notleft)/2));
	if (node->right != NULL) 
	{
		for (i=1; i <= node->edge_length && y+i < MAX_HEIGHT; i++) 
	{
		rprofile[y+i] = MAX(rprofile[y+i], x+i);
	}
	}
	rightProfile(node->left, x-node->edge_length-1, y+node->edge_length+1);
	rightProfile(node->right, x+node->edge_length+1, y+node->edge_length+1);
}

void computeEdgeLenght(asciinode *node) 
{
	int h, hmin, i, delta;
	if (node == NULL) return;
	computeEdgeLenght(node->left);
	computeEdgeLenght(node->right);
	if (node->right == NULL && node->left == NULL) 
	{
		node->edge_length = 0;
	} 
	else 
	{
		if (node->left != NULL) 
		{
			for (i=0; i<node->left->height && i < MAX_HEIGHT; i++) 
		{
				rprofile[i] = -INFINITY;
			}
			rightProfile(node->left, 0, 0);
			hmin = node->left->height;
		} 
		else 
			hmin = 0;
		if (node->right != NULL) 
		{
			for (i=0; i<node->right->height && i < MAX_HEIGHT; i++) 
		{
				lprofile[i] = INFINITY;
			}
			leftProfile(node->right, 0, 0);
			hmin = MIN(node->right->height, hmin);
		} 
		else 
			hmin = 0;
		delta = 4;
		for (i=0; i<hmin; i++) 
		{
			delta = MAX(delta, gap + 1 + rprofile[i] - lprofile[i]);
		}
		if (((node->left != NULL && node->left->height == 1) ||
			(node->right != NULL && node->right->height == 1))&&delta>4) 
		{
		delta--;
		}
			
		node->edge_length = ((delta+1)/2) - 1;
	}

	h = 1;
	if (node->left != NULL) 
	{
		h = MAX(node->left->height + node->edge_length + 1, h);
	}
	if (node->right != NULL) 
	{
		h = MAX(node->right->height + node->edge_length + 1, h);
	}
	node->height = h;
}

void printLevel(asciinode *node, int x, int level) 
{
	int i, isleft;
	if (node == NULL) return;
	isleft = (node->parent_dir == -1);
	if (level == 0) 
	{
		for (i=0; i<(x-print_next-((node->lablen-isleft)/2)); i++) 
		{
			printf(" ");
		}
		print_next += i;
		printf("%s", node->label);
		print_next += node->lablen;
	} 
	else if (node->edge_length >= level) 
	{
		if (node->left != NULL) 
		{
			for (i=0; i<(x-print_next-(level)); i++) 
		{
				printf(" ");
			}
			print_next += i;
			printf("/");
			print_next++;
		}
		if (node->right != NULL) 
		{
			for (i=0; i<(x-print_next+(level)); i++) 
		{
				printf(" ");
			}
			print_next += i;
			printf("\\");
			print_next++;
		}
	} 
	else 
	{
		printLevel(node->left, 
					x-node->edge_length-1, 
					level-node->edge_length-1);
		printLevel(node->right, 
					x+node->edge_length+1, 
					level-node->edge_length-1);
	}
}

void printAsciiTree(Tree * t) 
{
	asciinode *proot;
	int xmin, i;
	if (t == NULL) return;
	proot = buildAsciiTree(t);
	computeEdgeLenght(proot);
	for (i=0; i<proot->height && i < MAX_HEIGHT; i++) 
	{
		lprofile[i] = INFINITY;
	}
	leftProfile(proot, 0, 0);
	xmin = 0;
	for (i = 0; i < proot->height && i < MAX_HEIGHT; i++) 
	{
		xmin = MIN(xmin, lprofile[i]);
	}
	for (i = 0; i < proot->height; i++) 
	{
		print_next = 0;
		printLevel(proot, -xmin, i);
		printf("\n");
	}
	destroyAsciiTree(proot); 
}

Tree * preOrderWalkTreeInsertion(Node * node, Tree * tree)
{
	if(node == NULL)
		return tree;
	tree = insert(node->value, tree);
	tree = preOrderWalkTreeInsertion(node->left, tree);
	tree = preOrderWalkTreeInsertion(node->right, tree);
  	return tree;
}

void adaptAndPrint(BIT * tree) 
{
	Tree * root;
	root = NULL;    
	destroy(root);
	root = preOrderWalkTreeInsertion(tree->root, root);
	printAsciiTree(root);
	destroy(root);
}