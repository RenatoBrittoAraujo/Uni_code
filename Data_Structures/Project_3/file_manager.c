#include <stdio.h>
#include "person.h"

bool readFile(char * filename)
{
    FILE * file;
    file = fopen(filename, "r");

    if(file == NULL)
        return false;

    char read[300];
    Person * current;
    int position = 1;

    while(!feof(file))
    {
        fgets(read, 300, file);

        if(read[strlen(read) - 1] == '\n')
            read[strlen(read) - 1] = '\0';

        if(strlen(read) == 0)
            continue;
        
        if(read[0] == '$')
        {
            position = 1;
            continue;
        }

        if(position == 1)
        {
            
        }

    }

    if(fclose(file) == EOF)
        return false;

    return true;
}

int main()
{
    Person * joe = newPerson();
    setName("JOSE", joe);
    printf("%s\n", getName(joe));
    readFile("contact_list.resource");
}