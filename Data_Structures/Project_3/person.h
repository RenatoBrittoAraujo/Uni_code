#ifndef PERSON
#define PERSON

#include <stdbool.h>

#define name_size 101
#define address_size 101
#define phone_size 10
#define date_of_birth_size 8

struct Person
{
    char * name;
    char * phone;
    char * address;
    long long * identification;
    char * birth_date;
};

typedef struct Person Person;

// Return a new allocated instance of person struct
Person * newPerson();

// Free memory of person
void destroyPerson(Person * person);

// Setters

bool setName(char * name, Person * person);
bool setAddress(char * name, Person * person);
bool setPhone(char * name, Person * person);
bool setIdentification(long long int, Person * person);
bool setBirthDate(char * name, Person * person);

// Getters

char * getBirthDate(Person * person);
char * getAddress(Person * person);
char * getPhone(Person * person);
char * getName(Person * person);
long long int getIdentification(Person * person);

#endif