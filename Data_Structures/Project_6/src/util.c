#include <time.h>
#include <stdbool.h>
#include <stdlib.h>

#include "../inc/util.h"

// Private

// Public

int randInt(int l, int r)
{
    static int x = 1;
	if(x == 1)
		x = (time(NULL) + x) % 1000;
	x = (x / 2 * x - x * x * 2 + x * 3 + 2 + time(NULL) - time(NULL) * x) % 
		((x * x * (time(NULL) * x++ + 3)) % 10000 + 69420);
	
	srand(x++);
	return rand() % (r - l + 1) + l;
}

double randDouble(double l, double r)
{
	double val = (double) (randInt(0, 10000) + randInt(0, 10000)) / 20000.0;

	return val * (r - l) + l; 
}

int * randomIntPermutation(int listSize)
{
	int * list = (int *) malloc(sizeof(int) * listSize);
    for(int i = 0; i < listSize; i++)
        list[i] = i + 1;
    for(int i = 0; i < listSize * 100; i++)
    {
        int swapIndex = randInt(0, listSize - 1);
        int temp = list[i % listSize];
        list[i % listSize] = list[swapIndex];
        list[swapIndex] = temp;
    }
	return list;
}