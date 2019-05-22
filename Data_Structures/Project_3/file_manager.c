#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "person.h"
#include "linked_list.h"

LinkedList * readFile(char * filename)
{
    FILE * file;
    file = fopen(filename, "r");

    if(file == NULL)
        file = fopen(filename, "w");

    LinkedList * list = newLinkedList();

    char read[300];
    Person * current;
    int position = 0;

    while(!feof(file))
    {
        fgets(read, 300, file);

        if(read[strlen(read) - 1] == '\n')
            read[strlen(read) - 1] = '\0';

        if(strlen(read) == 0)
            continue;
        
        if(read[0] == '$')
        {
            position = 0;
            continue;
        }
        else position++;

        if(position == 1)
        {
            current = newPerson();
            setName(read, current);
        }

        if(position == 2)
            setPhone(read, current);

        if(position == 3)
            setAddress(read, current);
        
        if(position == 4)
            setIdentification(atoll(read), current);

        if(position == 5)
        {
            read[8] = '\0';
            setBirthDate(read, current);
            sortAddToLinkedList(current, list);
            current = newPerson();
            position = 0;
        }
    }
    fclose(file);
    return list;
}

void saveFile(char * filename, LinkedList * list)
{
    FILE * file = fopen(filename, "w");
    Node * current_node = list->root;
    while(current_node != NULL)
    {
        Person * current_person = current_node->person;
        fprintf(file, "%s\n%s\n%s\n%llu\n%s\n$\n",  getName(current_person), getPhone(current_person),
                                                    getAddress(current_person), getIdentification(current_person),
                                                    getBirthDate(current_person));
        next(&current_node);
    }
    fclose(file);
}