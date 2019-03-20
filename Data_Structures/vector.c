#include <stdio.h>
#include <stdlib.h>

class INTVector{
	
private:
	int * matrix;
	int v_size;
	int memalloc;

	bool isInBounds(int index){
		return !(index < 0 or index >= v_size);
	}

	void memcut(){
		if(memalloc < 2)return;
		matrix = (int *) realloc(matrix, sizeof(int) * (memalloc / 2));
		memalloc >>= 1;
	}

	void memgrow(){
		matrix= (int *) realloc(matrix, sizeof(int) * memalloc * 2);
		memalloc <<= 1;
	}

public:
	INTVector(){
		v_size = 0;
		matrix = (int *) malloc(sizeof(int));
		memalloc = 1;
	}

	void push(int in, bool verbose = 0){

		if(v_size + 1 >= memalloc){

				memgrow();

				if(verbose)printf("Allocated memory\n");
		}

		matrix[v_size] = in;

		v_size++;
	}

	int size(){
		return v_size;
	}

	int at(int index, bool verbose = 0){
	
		if(!isInBounds(index)){

			if(verbose)printf("Not found\n");
			return 0;

		}
	
		return matrix[index];
	}

	void pop(bool verbose = 0){
		
		if(v_size > 0 and memalloc > v_size * 2){

			memcut();
			if(verbose)printf("Cleaned memory\n");
		
		}

		if(v_size > 0)v_size--;
	}

	void print_stats(){

		int i;
		
		printf("SIZE = %d\n",size());
		printf("ALLOCATION = %d\n",memalloc);
		
		for(i = 0; i < size(); i++)
			printf("%d ",at(i));
		
		printf("\n");
	
	}

	void remove(int index, bool verbose = 0){
	
		if(!isInBounds(index))return;
		
		int i;

		if(verbose)printf("Item %d in position %d removed\n", matrix[index], index);

		for(i = index; i < v_size; i++){
			matrix[i] = matrix[i + 1];
		}

		v_size--;
		memcut();

	}

};

int main(){
	
	INTVector v;

	int n;

	scanf("%d",&n);

	int i,x;

	for(int i = 0; i < n; i++){
		scanf("%d",&x);
		v.push(x);
	}

	//v.print_stats();
		
	int tr;

	scanf("%d",&tr);

	v.remove(tr);

	//v.print_stats();
	
}
