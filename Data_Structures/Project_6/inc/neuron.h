#ifndef NN_NEURON_H
#define NN_NEURON_H

typedef struct Neuron Neuron;

struct Neuron
{
    double * weights;
    int inputSize;
    double bias;
};

Neuron * createNeuron(int inputSize);
Neuron * createCustomNeuron(int inputSize, double customWeight);

void destroyNeuron(Neuron * neuron);

// Returns the neuronal output based on input, weights, biases and activation function
double neuronOutput(Neuron * neuron, double * input);

#endif