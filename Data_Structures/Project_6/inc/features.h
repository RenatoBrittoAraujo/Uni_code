#ifndef NN_FEATURES_H
#define NN_FEATURES_H

// Generates feature list from 'resources/dataset/[datasetType]/[datasetType]_[ID].txt'
double ** getFeatures(char * datasetType, int datasetSize, int * datasetIDs);

int getFeatureListSize();

// Randomly permutes a feature list
void permuteFeatures(double ** features, int featureListSize);

#endif