#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "object.h"

#define SIZE 100000

class HashTable{
private:
	
	struct Object * table[SIZE];
	int tableSize;

public:

	HashTable(){
		
		tableSize = 0;

	}
	
	int hashFunction(int identifier){
		
		int hash = identifier % SIZE;			

		return hash;
	}

	struct Object * search(int identifier, bool complexityVerbose = false){

		int hash = hashFunction(identifier);

		Object * v = table[hash];

		if(complexityVerbose)
			printf("Is element Null: %s\n", v == NULL ? "Yes" : "No");
		
		while(table[hash] != NULL){

			if(table[hash]->identifier == identifier)
				return table[hash];

			hash = (hash + 1) % SIZE;

		}

		return NULL;

	}

	void insert(int identifier, char * data, bool verbose = false){

		if(search(identifier) != NULL){

			printf("Identifier already used\n");
			return;

		}		

		int hash = hashFunction(identifier);
		
		while(table[hash] != NULL){
			
			hash = (hash + 1) % SIZE;

		}
	
		struct Object * new_object = (struct Object *) malloc(sizeof(struct Object));
		
		new_object->identifier = identifier;

		int i = 0;
		while(*data != '\0')
			new_object->data[i++] = *data++;

		tableSize++;
		table[hash] = new_object;
	}

	void erase(int identifier){

		int hash = hashFunction(identifier);

		while(table[hash] != NULL){
			
			if(table[hash]->identifier == identifier){

				free(table[hash]);
				tableSize--;
				return;

			}

		}

	}

	int size(){

		return tableSize;

	}
};

int main(){

	HashTable hash;

	char a[] = "Michel Telo";
	char b[] = "Goa Gill";
	char c[] = "Sajanka";
	char d[] = "Astrix";

	hash.insert(120, a, true);
	hash.insert(1, b);
	hash.insert(121, c);
	hash.insert(1002, d);

	struct Object * ret = hash.search(120, true);
	printf("%d -> %s\n", ret->identifier, ret->data);
	ret = hash.search(121, true);
	printf("%d -> %s\n", ret->identifier, ret->data);
	ret = hash.search(1, true);
	printf("%d -> %s\n", ret->identifier, ret->data);
	ret = hash.search(1002, true);
	printf("%d -> %s\n", ret->identifier, ret->data);
	ret = hash.search(122, true);

	if(ret != NULL)printf("%d -> %s\n", ret->identifier, ret->data);
	else printf("Not found\n");

	printf("Now erasing 120\n");

	hash.erase(120);
	ret = hash.search(120);
	if(ret == NULL)printf("120 not found\n");

	printf("SIZE = %d\n", hash.size());
	return 0;
}
