#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "person.h"

typedef struct Person Person;

Person * newPerson()
{
    Person * person = (Person *) malloc(sizeof(Person));
    person->name = (char *) malloc(sizeof(char) * name_size);
    person->phone = (char *) malloc(sizeof(char) * phone_size);
    person->address = (char *) malloc(sizeof(char) * address_size);
    person->birth_date = (char *) malloc(sizeof(char) * date_of_birth_size);
    person->identification = (unsigned long long *) malloc(sizeof(unsigned long long));
    return person;
}


void destroyPerson(Person * person)
{
    free(person->name);
    free(person->phone);
    free(person->address);
    free(person->birth_date);
    free(person->identification);
    free(person);
}


bool setName(char * name, Person * person)
{
    if(strlen(name) >= name_size)
        return false;

    if(strlen(name) == 0)
        return false;

    strcpy(person->name, name);
    
    return true;
}

char * getName(Person * person)
{
    char * name = person->name;
    return name;
}

bool setPhone(char * phone, Person * person)
{
    if(strlen(phone) != phone_size)
        return false;

    if(phone[5] != '-')
        return false;

    strcpy(person->phone, phone);
    
    return true;
}

char * getPhone(Person * person)
{
    char * phone = person->phone;
    return phone;
}

bool setAddress(char * address, Person * person)
{
    if(strlen(address) >= address_size)
        return false;

    if(strlen(address) == 0)
        return false;

    strcpy(person->address, address);
    
    return true;
}

char * getAddress(Person * person)
{
    char * address = person->address;
    return address;
}

bool setBirthDate(char * birth_date, Person * person)
{
    if(strlen(birth_date) != date_of_birth_size)
        return false;

    if(birth_date[2] != '/' || birth_date[5] != '/')
        return false;

    strcpy(person->birth_date, birth_date);
    
    return true;
}

char * getBirthDate(Person * person)
{
    char * birth_date = person->birth_date;
    return birth_date;
}

bool setIdentification(long long int identification, Person * person)
{
    *(person->identification) = identification;
    return true;
}

long long int getIdentification(Person * person)
{
    return *(person->identification);
}