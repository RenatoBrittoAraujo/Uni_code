#include <stdlib.h>
#include <math.h>

#include "../inc/neuron.h"
#include "../inc/util.h"

// M_E from math.h does not work on some computers
const double e = 2.7182818284590452353602874;

// Private

double sigmoid(double x)
{
    return 1.0 / (1.0 + pow(e, -x));
}

// Public

Neuron * createNeuron(int inputSize)
{
    Neuron * newNeuron = (Neuron *) malloc(sizeof(Neuron));
    newNeuron->inputSize = inputSize;
    double * inputWeight = ((double *) malloc(sizeof(double) * inputSize));
    for(int i = 0; i < inputSize; i++)
    {
        inputWeight[i] = randDouble(-1.0, 1.0);
    }
    newNeuron->weights = inputWeight;
    newNeuron->bias = randDouble(-1.0, 1.0);
    return newNeuron;
}

Neuron * createCustomNeuron(int inputSize, double customWeight)
{
    Neuron * newNeuron = (Neuron *) malloc(sizeof(Neuron));
    newNeuron->inputSize = inputSize;
    double * inputWeight = ((double *) malloc(sizeof(double) * inputSize));
    for(int i = 0; i < inputSize; i++)
    {
        inputWeight[i] = customWeight;
    }
    newNeuron->weights = inputWeight;
    newNeuron->bias = 0;
    return newNeuron;
}

void destroyNeuron(Neuron * neuron)
{
    if(neuron == NULL)
        return;
    free(neuron->weights);
    free(neuron);
}

double neuronOutput(Neuron * neuron, double * input)
{
    double sum = 0;
    for(int i = 0; i < neuron->inputSize; i++)
    {   
        sum += input[i] * neuron->weights[i];
    }
    sum += neuron->bias;
    sum /= (double) (neuron->inputSize);
    double result = sigmoid(sum);
    return result;
}