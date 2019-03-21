#include <stdio.h>
#include <stdlib.h>

#include "sp_node.h"

typedef struct SPNode Node;

class Stack{

private:

	Node * end;
	int v_size;

public:

	Stack(){
		
		end = (Node *) malloc(sizeof(Node *));
		v_size = 0;
		end->pointer = NULL;

	}

	void push(int value){
	
		Node * new_node = (Node *) malloc(sizeof(Node *));
		new_node->value = value;
		new_node->pointer = end;
		end = new_node;
		v_size++;

	}

	void pop(){

		Node * last = end->pointer;
		if(last->pointer == NULL)return;
		free(end);
		end = last;
		v_size--;	
	
	}

	int top(){
		if(v_size > 0)
			return end->value;

		else{
			printf("Empty stack\n");
			return 0;
		}
	}

	int size(){
		return v_size;
	}

};


int main(){

	Stack st;

	int n;
	scanf("%d",&n);

	int x;
	for(int i = 0; i < n; i++){
		scanf("%d",&x);
		st.push(x);
	}

	for(int i = 0; i < n; i++){
		printf("%d ",st.top());
		st.pop();
	}

	printf("\n");

	return 0;

}
