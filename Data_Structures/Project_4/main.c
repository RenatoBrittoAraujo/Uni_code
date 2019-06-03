#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include "queue.h"

const int timeStep = 5;

char flightNumbers[][7] = {"VG3001", "JJ4404", "LN7001", "TG1501", "GL7602", "TT1010", "AZ1009", "AZ1008", "AZ1010", "TG1506", "VG3002", "JJ4402", "GL7603", "RL7880", "AL0012", "TT4544", "TG1505", "VG3003", "JJ4403", "JJ4401", "LN7002", "AZ1002", "AZ1007", "GL7604", "AZ1006", "TG1503", "AZ1003", "JJ4403", "AZ1001", "LN7003", "AZ1004", "TG1504", "AZ1005", "TG1502", "GL7601", "TT4500", "RL7801", "JJ4410", "GL7607", "AL0029", "VV3390", "VV3392", "GF4681", "GF4690", "AZ1020", "JJ4435", "VG3010", "LF0920", "AZ1065", "LF0978", "RL7867", "TT4502", "GL7645", "LF0932", "JJ4434", "TG1510", "TT1020", "AZ1098", "BA2312", "VG3030", "BA2304", "KL5609", "KL5610", "KL5611"};

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

void swapFlights(Flight ** flightList, int p1, int p2)
{
    Flight * temp = flightList[p1];
    flightList[p1] = flightList[p2];
    flightList[p2] = temp;
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
        swapFlights(flightList, i, randInt(0, numberOfFlights - 1));
    }
    free(randomOrder);
    return flightList;
}

int countLandings(Flight ** flights, int numberOfFlights)
{
    int approachNumber = 0;
    for(int i = 0; i < numberOfFlights; i++)
    {
        approachNumber += flights[i]->landing;
    }
    return approachNumber;
}

Queue * getSortedLandings(Flight ** flightlist, int numberOfFlights)
{
    int numberOfLandings = countLandings(flightlist, numberOfFlights);
    Flight ** landingsArray = (Flight **) malloc(sizeof(Flight *) * (1 + numberOfLandings));
    int index = 0;
    for(int i = 0; i < numberOfFlights; i++)
    {
        if(flightlist[i]->landing)
        {
            landingsArray[index++] = flightlist[i];
        }
    }
    for(int i = 0; i < index; i++)
    {
        for(int j = i + 1; j < index; j++)
        {
            if(landingsArray[i]->fuel > landingsArray[j]->fuel)
            {
                swapFlights(landingsArray, i, j);
            }
        }
    }
    Queue * landings = (Queue *) malloc(sizeof(Queue));
    initializeQueue(landings);
    for(int i = numberOfLandings - 1; i >= 0; i--)
    {
        add(landingsArray[i], landings);
    }
    return landings;
}  

Queue * getTakeoffs(Flight ** flightlist, int numberOfFlights)
{
    Queue * takeoffs = (Queue *) malloc(sizeof(Queue));
    initializeQueue(takeoffs);
    int index = 0;
    for(int i = 0; i < numberOfFlights; i++)
    {
        if(!(flightlist[i]->landing))
        {
            add(flightlist[i], takeoffs);
        }
    }
    return takeoffs;
}

void printEvent(Flight * flight, int runway, int time)
{
    time %= (24 * 60);
    printf("Codigo de voo: %s\n",   flight->flightNumber);
    printf("Status: %s\n", flight->landing ? "Pouso" : "Decolagem");
    printf("Horario do inicio do procedimento: %.2d:%.2d\n", time / 60, time % 60);
    printf("Pista de pouso: %d\n", runway);
    printf("\n\n");
}

int main()
{
    int numberOfFlights = randInt(20, 64);
    Flight ** flights = generateFlightList(numberOfFlights);
    int currentTime = randInt(0, 24 * 60 - 1);

    printf("Aeroporto de Brasilia\nHorario inicial: %.2d:%.2d\n", currentTime / 60, currentTime % 60);
    printf("Fila de pedidos: \n");
    for(int i = 0; i < numberOfFlights; i++)
    {
        printf(" - Numero de voo: %s | %s | ", flights[i]->flightNumber, (flights[i]->landing ? "  pouso  " : "decolagem"));
        if(flights[i]->landing)
        {
            printf("Combustivel: %d", flights[i]->fuel);
        }
        printf("\n");
    }

    int numberOfLandings = countLandings(flights, numberOfFlights);
    int numberOfTakeoffs = numberOfFlights - numberOfLandings;

    printf("Numero de voos: %d\nNumero de pousos: %d\nNumero de decolagens: %d\n\n", numberOfFlights, numberOfLandings, numberOfTakeoffs);
    printf("Lista de eventos:\n\n");
    
    Queue * landings = getSortedLandings(flights, numberOfFlights);
    Queue * takeoffs = getTakeoffs(flights, numberOfFlights);

    int runways[3] = {currentTime, currentTime, currentTime};

    while(!empty(landings) || !empty(takeoffs))
    {
        int landingCount = 0;
        Node * currentPosition = landings->back;
    
        int minTime = runways[0];
        if(runways[1] < minTime)
            minTime = runways[1];

        while(  currentPosition != NULL && 
             (  currentPosition->flight->fuel - (minTime - currentTime) / (5 * timeStep))  <= 0)
            currentPosition = currentPosition->last, landingCount++;

        if(landingCount > 2)
        {
            printf("[ALERTA GERAL DE DESVIO DE AERONAVE]\n\n");

            while(landingCount--)
            {
                int indexMin = 0;
                int time = runways[0];
                for(int i = 1; i < 3; i++)
                {   
                    if(runways[i] < time)
                    {
                        time = runways[i];
                        indexMin = i;
                    }
                }
                if( front(landings) != NULL && 
                    front(landings)->fuel - (runways[indexMin] - currentTime) / (5 * timeStep) < 0)
                {
                    printf("[ALERTA CRITICO, AERONAVE IRA CAIR]\n\n");
                }
                else
                {
                    printEvent(front(landings), indexMin + 1, runways[indexMin]);
                    runways[indexMin] += 4 * timeStep;
                }
                pop(landings);
            }
        }
        else
        {
            if(front(takeoffs) != NULL)
            {
                printEvent(front(takeoffs), 3, runways[2]);
                pop(takeoffs);
                runways[2] += 2 * timeStep;
            }

            if(front(landings) != NULL)
            {
                int indexMin = 0;
                int time = runways[0];
                for(int i = 1; i < 2; i++)
                {   
                    if(runways[i] < time)
                    {
                        time = runways[i];
                        indexMin = i;
                    }
                }
                if(front(landings)->fuel - (runways[indexMin] - currentTime) / (5 * timeStep) < 0)
                {
                    printf("[ALERTA CRITICO, AERONAVE IRA CAIR]\n\n");
                }
                else
                {
                    printEvent(front(landings), indexMin + 1, runways[indexMin]);
                    runways[indexMin] += 4 * timeStep;
                }
                pop(landings);
            }
        }
        
    }

    for(int i = 0; i < numberOfFlights; i++)
    {
        free(flights[i]);
    }
    free(flights);
    destroyQueue(landings);
    destroyQueue(takeoffs);

    return 0;
}