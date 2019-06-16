#ifndef NN_UTIL_H
#define NN_UTIL_H

// Returns random integer from [l,r] non-negative, smaller than 10000
int randInt(int l, int r);

// Returns random double from [l,r] non-negative
double randDouble(double l, double r);

// Returns a array filled with a random permutation of numbers from [1,listSize]
int * randomIntPermutation(int listSize);

// Normalizes floating point array
void normalize(double * list, int listSize);

#endif