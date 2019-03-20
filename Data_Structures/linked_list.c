#include <stdio.h>
#include <stdlib.h>

// Linked list node

struct Node{

	int value;
	Node * pointer;

};

// Linked list 

struct LinkedList{
	
	// Starting node, ending node, size of list

	Node * begin;
	Node * end;
	int v_size;

	// Constructor (starts with empty node)

	LinkedList(){

		begin = (Node *) malloc(sizeof(Node));
		begin->pointer = NULL;
		end = begin;
		v_size = 0;

	}

	// Pushes variable into the list by creating
	// a new node and point the last to the new
	// and finally turning the last node the new

	void push(int x){
			
		Node * new_end = (Node *) malloc(sizeof(Node));
		new_end->pointer = NULL;
		end->pointer = new_end;
		end->value = x;

		end = new_end;

		v_size++;

	}

	// For pop() function implementation, 
	// either we would store in each node it's parent
	// or do an O(n) search for the element which points to
	// the last, set it's pointer to null, free memory in the
	// last pointer and set the last as the iterator pointer

	// But, either case, this is a linked list so......
	
	int size(){
		
		return v_size;

	}

};

// Iterative search of linked list

void explore(const	LinkedList * l){
	
	Node * p = l->begin;
	int counter = 0;

	// While the current node doesn't point to NULL
	// (remember the end of the list, which contains an
	// null pointer, has NO VALUE, therefore don't display
	
	// Couldn't think of a way to do without occupying less than
	// sizeof(LinkedList) + sizeof(Node) * (NUMBER OF ELEMENTS + 1)
	// memory 

	while(p->pointer != NULL){

		printf("Position: %d | Value: %d\n", counter++, p->value);
		p = p->pointer;
	
	}

}

int main(){

	LinkedList l;

	int n;
	printf("Linked list size = ");
	scanf("%d", &n);

	printf("Now list the elements of linked list\n");
	
	while(n--){
		
		int x;
		scanf("%d",&x);
		l.push(x);

	}

	printf("Exploring linked list\n");

	explore(&l);

	printf("Linked list size = %d\n",l.size());

}
