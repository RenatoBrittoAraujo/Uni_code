/*
    Nome: Renato Britto Araujo
    Matricula: 180027239
 */


#include <stdio.h>
#include <stdlib.h>

#include "../inc/features.h"
#include "../inc/neural_network.h"
#include "../inc/util.h"

#define or ||
#define and &&

const int DATAPOINTS = 50;

int main(int argc, char ** argv)
{
    int neuronsInHiddenLayer = 100;
    int datasetSize = 50;
    double learningRate = 0.21;

    if(argc >= 2)
        neuronsInHiddenLayer = atoi(argv[1]);

    printf("Number of neurons in the middle layer: %d\n", neuronsInHiddenLayer);
    printf("Learning rate: %.2lf\n\n", learningRate);

    int * asphaltInputOrder = randomIntPermutation(DATAPOINTS);
    int * grassInputOrder = randomIntPermutation(DATAPOINTS);

    printf("Creating dataset features...\n\n");
    fflush(stdout);

    double ** alsphaltFeatures = getFeatures("asphalt", datasetSize, asphaltInputOrder);
    double ** grassFeatures = getFeatures("grass", datasetSize, grassInputOrder);

    NeuralNetwork * neuralNetwork = createNeuralNetwork(getFeatureListSize(), neuronsInHiddenLayer, datasetSize, learningRate);  

    int numberOfEpochs = 0;

    printf("\nRunning epochs...\n\n");
    fflush(stdout);

    do
    {
        permuteFeatures(grassFeatures, datasetSize);
        permuteFeatures(alsphaltFeatures, datasetSize);

        runEpoch(neuralNetwork, alsphaltFeatures, grassFeatures, datasetSize);
        numberOfEpochs++;

        printf("Epoch %d with MSE %.5lf\n", numberOfEpochs, getMSE(neuralNetwork));

        fflush(stdout);

    } while(getMSE(neuralNetwork) > 0.2 and numberOfEpochs < 1000);

    printf("\nNeural network went through %d epochs and has a MSE of %.5lf\n\n", numberOfEpochs, getMSE(neuralNetwork));

    int rights = 0;
    int tested = 0;

    int misslabledGrass = 0;
    int misslabledAsphalt = 0;

    for(int i = 0; i < datasetSize; i++)
    {
        double value = getNeuralnetworkOutput(neuralNetwork, alsphaltFeatures[i]);
        printf("ASPHALT CLASSIFICATION VALUE: %.6lf\n", value);
        if(value <= 0.5)
            rights++;
        else
            misslabledAsphalt++;
        tested++;
    }

    for(int i = 0; i < datasetSize; i++)
    {
        double value = getNeuralnetworkOutput(neuralNetwork, grassFeatures[i]);
        printf("  GRASS CLASSIFICATION VALUE: %.6lf\n", value);
        if(value > 0.5)
            rights++;
        else
            misslabledGrass++;
        tested++;
    }

    printf("\n\nOut of %d tested, %d yilded the right classification (%% %.5lf)\n", tested, rights, ((double) rights / (double) tested) * 100.0);
    printf("Misslabled grass as asphalt: %d (%% %.5lf)\n", misslabledGrass, ((double) misslabledGrass / (double) (tested / 2)) * 100.0);
    printf("Misslabled asphalt as grass: %d (%% %.5lf)\n", misslabledAsphalt, ((double) misslabledAsphalt / (double) (tested / 2)) * 100.0);

    destroyNeuralNetwork(neuralNetwork);

    return 0;
}