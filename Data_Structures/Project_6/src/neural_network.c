#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <stdbool.h>

#include "../inc/neural_network.h"
#include "../inc/util.h"

// Private

double fowardPropagation(NeuralNetwork * net, double * input, double * inputLayerOutput, double * hiddenLayerOutput)
{
    bool freeInputLayerOutput = false;
    bool freeHiddenLayerOutput = false;
    if(inputLayerOutput == NULL)
    {
        inputLayerOutput = (double *) malloc(sizeof(double) * net->inputLayerSize);
        freeInputLayerOutput = true;
    }
    if(hiddenLayerOutput == NULL)
    {
        hiddenLayerOutput = (double *) malloc(sizeof(double) * net->hiddenLayerSize);
        freeHiddenLayerOutput = true;
    }

    // Calculating neuron output for input layer

    for(int i = 0; i < net->inputLayerSize; i++)
    {
        inputLayerOutput[i] = neuronOutput(net->inputLayer[i],  input + i);
    }

    // Calculating neuron output for hidden layer

    for(int i = 0; i < net->hiddenLayerSize; i++)
    {
        hiddenLayerOutput[i] = neuronOutput(net->hiddenLayer[i], inputLayerOutput);
    }

    if(freeInputLayerOutput)
        free(inputLayerOutput);
    if(freeHiddenLayerOutput)
        free(hiddenLayerOutput);
    
    return neuronOutput(net->endNeuron, hiddenLayerOutput);
}

void backwardPropagation(NeuralNetwork * net, double error, double endValue, double * hiddenLayerOutput, double * inputLayerOutput, double * input)
{
    // Derivative of sigmoid function times error (error = output - expected)

    double endNodeGradient = error * (1 - endValue) * endValue;

    // Adjusting bias for end node

    net->endNeuron->bias -= endNodeGradient * net->learningRate;

    for(int i = 0; i < net->hiddenLayerSize; i++)
    {
        // Gradient of hidden layer node i

        double currentNodeGradient = endNodeGradient * net->endNeuron->weights[i];

        // Adjustng bias

        net->hiddenLayer[i]->bias -= currentNodeGradient * net->learningRate * hiddenLayerOutput[i] * (1 - hiddenLayerOutput[i]);

        // Adjusting weights

        for(int j = 0; j < net->inputLayerSize; j++)
        {
            net->hiddenLayer[i]->weights[j] -= net->learningRate * currentNodeGradient * inputLayerOutput[j];
        }
    }

    // Note that the weights of end neuron were only altered after being used in the middle layer

    for(int i = 0; i < net->endNeuron->inputSize; i++)
    {
        net->endNeuron->weights[i] -= net->learningRate * endNodeGradient * hiddenLayerOutput[i];
    }
}

// Public

NeuralNetwork * createNeuralNetwork(int inputLayerSize, int hiddenLayerSize, int datasetSize, double learningRate)
{

    NeuralNetwork * net = (NeuralNetwork *) malloc(sizeof(NeuralNetwork));
    net->learningRate = learningRate;

    // Initializing layers with dummy weights and biases
    
    net->inputLayer = (Neuron **) malloc(sizeof(Neuron *) * inputLayerSize);
    net->inputLayerSize = inputLayerSize;
    for(int i = 0; i < inputLayerSize; i++)
    {
        net->inputLayer[i] = createCustomNeuron(1, 1);
    }
    net->hiddenLayer = (Neuron **) malloc(sizeof(Neuron *) * hiddenLayerSize);
    net->hiddenLayerSize = hiddenLayerSize;
    for(int i = 0; i < hiddenLayerSize; i++)
    {
        net->hiddenLayer[i] = createNeuron(inputLayerSize);
    }
    net->endNeuron = createNeuron(hiddenLayerSize);

    // Initializing dataset information

    net->datasetSize = datasetSize * 2;
    net->epochErrorList = (double *) malloc(sizeof(double) * datasetSize * 2);

    return net;
}

void destroyNeuralNetwork(NeuralNetwork * net)
{
    for(int i = 0; i < net->inputLayerSize; i++)
    {
        destroyNeuron(net->inputLayer[i]);
    }
    free(net->inputLayer);
    for(int i = 0; i < net->hiddenLayerSize; i++)
    {
        destroyNeuron(net->hiddenLayer[i]);
    }
    free(net->hiddenLayer);
    destroyNeuron(net->endNeuron);
    free(net->epochErrorList);
    free(net);
}

void runEpoch(NeuralNetwork * net, double ** datasetA, double ** datasetB, int datasetSize)
{
    int * order = randomIntPermutation(datasetSize * 2);
    int datasetAindex = 0;
    int datasetBindex = 0;

    for(int i = 0; i < datasetSize * 2; i++)
    {
        double * input;
        double expected;

        double * inputLayerOutput = (double *) malloc(sizeof(double) * net->inputLayerSize);
        double * hiddenLayerOutput = (double *) malloc(sizeof(double) * net->hiddenLayerSize);

        //  if the integer order[i] is pair in the random permutation, run propagation on dataset type 1 else dataset type 2 

        if(order[i] & 1)
        {
            expected = 0.0;
            input = datasetA[datasetAindex++];
        }
        else
        {
            expected = 1.0;
            input = datasetB[datasetBindex++];
        }

        double netOutput = fowardPropagation(net, input, inputLayerOutput, hiddenLayerOutput);

        double error = (netOutput - expected);

        net->epochErrorList[i] = error;

        backwardPropagation(net, error, netOutput, hiddenLayerOutput, inputLayerOutput, input);

        free(inputLayerOutput);
        free(hiddenLayerOutput);
    }
    free(order);
}

double getMSE(NeuralNetwork * net)
{
    double sum = 0;
    for(int i = 0; i < net->datasetSize; i++)
    {
        sum += pow(fabs(net->epochErrorList[i]), 2.0);
    }
    return sum / (double) (net->datasetSize);
}

double getNeuralnetworkOutput(NeuralNetwork * net, double * input)
{
    return fowardPropagation(net, input, NULL, NULL);
}