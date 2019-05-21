#ifndef FILE_MANAGER
#define FILE_MANAGER

#include <stdbool.h>
#include "linked_list.h"


bool readFile(char * filename);
bool saveFile(LinkedList * list);



#endif