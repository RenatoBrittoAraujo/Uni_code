#include <stdio.h>
#include <stdlib.h>

#include "sp_node.h"

typedef struct SPNode Node;

class Queue{

private:

	Node * begin;
	Node * end;
	int v_size;

public:

	Queue(){

		Node * front = (Node *) malloc(sizeof(Node *));
		front->pointer = NULL;
		end = begin = front;
		v_size = 0;
	
	}

	void push(int value){

		Node * new_node = (Node *) malloc(sizeof(Node *));
		end->pointer = new_node;
		end->value = value;
		end = new_node;
		v_size++;

	}

	int front(){
		if(begin->pointer == NULL){
			printf("Empty queue\n");
			return 0;
		}
		return begin->value;
	}

	void pop(){

		Node * second = begin->pointer;
		if(second == NULL)return;
		free(begin);
		begin = second;
		v_size--;
		
	}

	int size(){
		return v_size;
	}

};

int main(){
	
	int n;
	scanf("%d",&n);

	int x;

	Queue q;

	for(int i = 0; i < n; i++){
	
		scanf("%d",&x);
		q.push(x);

	}

	for(int i = 0; i < n; i++){
		
		printf("%d ", q.front());
		q.pop();

	}
	
	printf("\n");

	return 0;

}
