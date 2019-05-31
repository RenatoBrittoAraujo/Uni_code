#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>

char flightNumbers[][7] = {"VG3001", "JJ4404", "LN7001", "TG1501", "GL7602", "TT1010", "AZ1009", "AZ1008", "AZ1010", "TG1506", "VG3002", "JJ4402", "GL7603", "RL7880", "AL0012", "TT4544", "TG1505", "VG3003", "JJ4403", "JJ4401", "LN7002", "AZ1002", "AZ1007", "GL7604", "AZ1006", "TG1503", "AZ1003", "JJ4403", "AZ1001", "LN7003", "AZ1004", "TG1504", "AZ1005", "TG1502", "GL7601", "TT4500", "RL7801", "JJ4410", "GL7607", "AL0029", "VV3390", "VV3392", "GF4681", "GF4690", "AZ1020", "JJ4435", "VG3010", "LF0920", "AZ1065", "LF0978", "RL7867", "TT4502", "GL7645", "LF0932", "JJ4434", "TG1510", "TT1020", "AZ1098", "BA2312", "VG3030", "BA2304", "KL5609", "KL5610", "KL5611"};

struct Flight
{
    int fuel;
    bool landing;
    char * flightNumber;
};

typedef struct Flight Flight;

int randInt(int l, int r)
{
    if(r < l)
        return 0;
    static int x = 0;
    x = ((int)time(NULL) + x * x + 3 + x) % 10000;
    return ((int)time(NULL) + x) % (r - l + 1) + l;
}

void swapInt(int * a, int * b)
{   
    int temp = *a;
    *a = *b;
    *b = temp;
}

int * generateRandomNumberSequence(int sequenceSize)
{
    int * sequence = (int *) malloc(sizeof(int) * sequenceSize);
    for(int i = 0; i < sequenceSize; i++)
        sequence[i] = i;
    for(int i = 0; i < sequenceSize; i++)
        swapInt(&sequence[i], &sequence[randInt(0, sequenceSize - 1)]);
    return sequence;
}

Flight * generateRandomFlight()
{
    Flight * newFlight = (Flight *) malloc(sizeof(Flight));
    newFlight->fuel = randInt(0, 12);
    return newFlight;
}

Flight ** generateFlightList(int numberOfFlights)
{
    int approaches = randInt(10, numberOfFlights / 2);
    Flight ** flightList = (Flight **) malloc(sizeof(Flight *) * numberOfFlights);
    int * randomOrder = generateRandomNumberSequence(numberOfFlights);
    for(int i = 0; i < numberOfFlights; i++)
    {
        flightList[i] = generateRandomFlight();
        flightList[i]->landing = (i < approaches ? true : false);
        flightList[i]->flightNumber = flightNumbers[randomOrder[i]];
    }
    for(int i = 0; i < numberOfFlights; i++)
    {
        Flight * temp = flightList[i];
        int randomPosition = randInt(0, numberOfFlights - 1);
        flightList[i] = flightList[randomPosition];
        flightList[randomPosition] = temp;
    }
    free(randomOrder);
    return flightList;
}

void sortList(Flight ** flightlist)
{

}

int main()
{
    int numberOfFlights = randInt(20, 64);
    Flight ** flights = generateFlightList(numberOfFlights);
    int currentTime = randInt(0, 24 * 60 - 1);
    printf("Aeroporto de Brasilia\nHorarios inicial: %d:%d\n", currentTime / 60, currentTime % 60);
    printf("Fila de pedidos: \n");
    for(int i = 0; i < numberOfFlights; i++)
    {
        printf(" - Numero de voo: %s | %s | Combustivel: %d\n", flights[i]->flightNumber, (flights[i]->landing ? "  pouso  " : "decolagem"), flights[i]->fuel);
    }
    int approachNumber = 0;
    for(int i = 0; i < numberOfFlights; i++)
    {
        approachNumber += flights[i]->landing;
    }
    printf("Numero de voos: %d\nNumero de pousos: %d\n\n", numberOfFlights, approachNumber);
    printf("Lista de eventos:\n\n");
    for(int i = 0; i < numberOfFlights; i++)
    {
        printf("Codigo de voo: %s\n", flights[i]->flightNumber);
        printf("Status: %s\n", flights[i]->landing ? "Pouso" : "Decolagem");

        printf("\n\n");
    }


}