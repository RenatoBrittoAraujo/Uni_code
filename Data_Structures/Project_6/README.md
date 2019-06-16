# Project 6 - Neural Network

Simple neural network in C, it receives 536 inputs, 512 being the ILBP of the picture of a texture and the other 24 being the GLCM of the same picture, it then run through a hidden layer with a variable number of neurons and finally goes to a single end neuron with a floating point output, < 0.5 means it predicts it's a picture of asphalt and > 0.5 means a grass prediction. The activation function used is sigmoid.
 
Dataset link:  https://drive.google.com/file/d/1PzFVBqswF5xvbIxcwCOC0A4NZGehAIOZ/view

To use put the dataset info into the file structure 'resources/dataset/[datasetType]/[datasetType]_[datasetItemID].txt'

To compile
```
make
```

To run standard configuration
```
make run
```

To clean binary files
```
make clean
```

Custom option
```
make run hidden_layer_neurons=n
```
Switch 'n' with any integer to change the number of neurons in the hidden layer of the network 

The best configurations i've found were:

    Neurons in the hidden layer: [100, 300]

    Learning rate: [0.1, 0.2]
