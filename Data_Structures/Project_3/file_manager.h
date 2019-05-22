#ifndef FILE_MANAGER
#define FILE_MANAGER

#include "linked_list.h"

LinkedList * readFile(char * filename);
void saveFile(char * filename, LinkedList * list);

#endif