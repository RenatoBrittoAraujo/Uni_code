#ifndef NN_NEURAL_NETWORK_H
#define NN_NEURAL_NETWORK_H

#include "./neuron.h"

typedef struct NeuralNetwork NeuralNetwork;

struct NeuralNetwork
{
    Neuron ** inputLayer;
    Neuron ** hiddenLayer;
    Neuron * endNeuron;

    int inputLayerSize;
    int hiddenLayerSize;

    int datasetSize;
    double * epochErrorList;

    double learningRate;
};

NeuralNetwork * createNeuralNetwork(int inputLayerSize, int hiddenLayerSize, int datasetSize, double learningRate);
void destroyNeuralNetwork(NeuralNetwork * net);

// Retunrns the mean square error of the last epoch
double getMSE(NeuralNetwork * net);

// Runs an epoch on the datasets, foward propagation and backward propagation
void runEpoch(NeuralNetwork * net, double ** datasetA, double ** datasetB, int datasetSize);

// Runs a foward propagation with the input and returns the network ouput
double getNeuralnetworkOutput(NeuralNetwork * net, double * input);

#endif