#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "file_manager.h"
#include "linked_list.h"
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

void displayPerson(Person * person)
{
    printf("Nome: %s\n", getName(person));
    printf("Telefone: %s\n", getPhone(person));
    printf("Endereco: %s\n", getAddress(person));
    printf("CPF: %llu\n", getIdentification(person));
    printf("Data de nascimento: %s\n", getBirthDate(person));
}

LinkedList * list;

void findPeople()
{
    printf("Digite o nome da consulta: ");
    char buff[301];
    scanf("%300[^\n]", buff);
    printf("WTF\n");
    Node * found = getFirstNameInstance(buff, list);
    if(found == NULL)
    {
        printf("Nome nao encontrado!\n");
        return;
    }
    int counter = 1;
    while(found != NULL && !strcmp(found->person->name, buff))
    {
        printf(" - %d pessoa encontrada:\n", counter++);
        displayPerson(found->person);
    }
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

    list = readFile("contact_list.resources");
    if(list == NULL)
    {
        printf("Ocorreu um erro na leitura de arquivos, por favor reinicie o programa\n");
        exit(1);
    }

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

        saveFile("contact_list.resources", list);
    }

    return 0;
}