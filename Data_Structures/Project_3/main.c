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
    printf("Nome:                %s\n", getName(person));
    printf("Telefone:            %s\n", getPhone(person));
    printf("Endereco:            %s\n", getAddress(person));
    printf("CPF:                 %llu\n", getIdentification(person));
    printf("Data de nascimento:  %s\n", getBirthDate(person));
}

LinkedList * list;

void findPeople()
{
    printf("Digite o nome do registro a ser consultado: ");
    char buff[301];
    scanf(" %300[^\n]", buff);
    printf("\n");
    Node * found = getFirstNameInstance(buff, list);
    if(found == NULL)
    {
        printf("Registro nao encontrado!\n\n");
        return;
    }
    int counter = 0;
    while(found != NULL && !stringCompare(found->person->name, buff))
    {
        displayPerson(found->person);
        printf("\n");
        counter++;
        next(&found);
    }
    printf(" - %d registro%s encontrado%s\n\n", counter, (counter == 1 ? "" : "s"), (counter == 1 ? "" : "s"));
}

void sortAndDisplay()
{
    Node * current_node = list->root;
    int counter = 0;
    while(current_node != NULL)
    {
        if(current_node->person != NULL)
        {
            printf(" - Pessoa %d:\n", ++counter);
            displayPerson(current_node->person);
            printf("\n");
        }
        next(&current_node);
    }
    if(counter == 0)
        printf("Lista de contatos vazia!\n\n");
    else
        printf(" - %d registro%s encontrado%s\n\n", counter, (counter == 1 ? "" : "s"), (counter == 1 ? "" : "s"));
}

void insertPerson()
{
    Person * person = newPerson();
    char buff[300];
    long long int number;
    printf("Itens de ate 100 caracteres\n");
    do
    {
        printf("Nome: ");
        scanf(" %300[^\n]", buff);
    }while(!setName(buff, person));

    do{
        printf("Telefone (XXXXX-XXXX): ");
        scanf(" %300[^\n]", buff);
    }while(!setPhone(buff, person));
    
    do{
        printf("Endereco: ");
        scanf(" %300[^\n]", buff);
    }while(!setAddress(buff, person));

    do{
        printf("CPF (apenas numeros): ");
        scanf("%llu", &number);
    }while(!setIdentification(number, person));
    
    do{
        printf("Data de nascimento (XX/XX/XX): ");
        scanf(" %300[^\n]", buff);
    }while(!setBirthDate(buff, person));

    sortAddToLinkedList(person, list);
    printf("Registro criado com sucesso!\n\n");
}

void removePerson()
{
    printf("Digite o nome do resgistro a ser deletado: ");
    char buff[301];
    scanf(" %300[^\n]", buff);
    printf("\n");

    Node * found = getFirstNameInstance(buff, list);

    if(found == NULL)
    {
        printf("Registro nao encontrado!\n\n");
        return;
    }

    int regCount = 0;

    Node * current_node = found;

    while(current_node != NULL && !stringCompare(current_node->person->name, buff))
    {
        printf("Indice %d:\n", ++regCount);
        displayPerson(current_node->person);
        printf("\n");
        next(&current_node);
    }

    current_node = found;

    if(regCount > 1)
    {
        int index = -1;
        while(index < 1 || index > regCount)
        {
            printf("Digite o indice do registro a ser removido: ");
            scanf("%d", &index);
        }
        regCount = 1;
        while(current_node != NULL && !stringCompare(current_node->person->name, buff))
        {
            if(regCount == index)
                break;
            regCount++;
            next(&current_node);
        }
    }

    printf("Tem certeza que deseja deletar registro (S ou N)? ");
    char option;
    scanf(" %c", &option);

    if(option == 's' || option == 'S')
    {
        removeFromLinkedList(current_node, list);
        printf("Registro removido\n\n");
        return;
    }
    printf("Registro nao removido\n\n");
}

int main(int argc, char ** argv)
{
    printf("Bem vindo a agenda de contatos!\n\n");

    list = readFile("contact_list.resource");
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

        saveFile("contact_list.resource", list);
    }

    return 0;
}
