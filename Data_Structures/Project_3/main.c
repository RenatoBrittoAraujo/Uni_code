#include <stdlib.h>
#include <stdio.h>

#include "file_manager.h"
#include "person.h"

#define INSERT 1
#define REMOVE 2
#define FIND_BY_KEY 3
#define SORT_BY_KEY 4
#define EXIT_PROGRAM 0

void showOptions()
{   
    printf("Opcoes:\n");
    printf("%d. Inserir contato\n", INSERT);
    printf("%d. Remover contato\n", REMOVE);
    printf("%d. Encontrar contatos\n", FIND_BY_KEY);
    printf("%d. Ordenar por nomes\n", SORT_BY_KEY);
    printf("%d. Sair\n", EXIT_PROGRAM);
}

void findPeople()
{

}

void sortAndDisplay()
{

}

void insertPerson()
{

}

void removePerson()
{

}

int main(int argc, char ** argv)
{
    printf("Bem vindo a agenda de contatos!\n\n");

    while(1)
    {
        showOptions();
        printf("\n");

        int option = -1;
        char * flash = "";
        while(option < EXIT_PROGRAM || option > SORT_BY_KEY)
        {
           printf("Selecao%s: ", flash);
           scanf("%d", &option);
           flash = " (anterior valida)";
        }

        printf("\n");

        switch (option)
        {
        case EXIT_PROGRAM:
            exit(0);
            break;
        case INSERT:
            insertPerson();
            break;
        case REMOVE:
            removePerson();
            break;
        case FIND_BY_KEY:
            findPeople();
            break;
        case SORT_BY_KEY:
            sortAndDisplay();
            break;
        }
    }

    return 0;
}