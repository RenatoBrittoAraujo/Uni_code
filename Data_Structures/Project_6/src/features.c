#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "../inc/features.h"
#include "../inc/util.h"

// Private

const int GLCM_SIZE = 24;
const int ILBP_SIZE = 512;
const int FEATURE_LIST_SIZE = 536;

const int PIXEL_MAX = 256;
const int ENUM_DIRECTIONS = 8;
const int IMAGE_MATRIX_SIDE = 1025;

const int di[] = {-1, -1, -1,  0,  0,  1,  1,  1};
const int dj[] = {-1,  0,  1, -1,  1, -1,  0,  1};

double * GLCM(int ** image)
{
	double GLCM_matriz[PIXEL_MAX][PIXEL_MAX];
	double output[3 * 8];
	double * features = malloc(sizeof(double) * GLCM_SIZE);
	for(int k = 0; k < ENUM_DIRECTIONS; k++){
		memset(GLCM_matriz, 0.0, sizeof GLCM_matriz);
		double numberOfElements = 0;
		for(int i = (di[k] == -1 ? 1 : 0); i < IMAGE_MATRIX_SIDE - (di[k] == 1 ? 1 : 0); i++){
			for(int j = (dj[k] == -1 ? 1 : 0); j < IMAGE_MATRIX_SIDE - (dj[k] == 1 ? 1 : 0); j++){
				GLCM_matriz[image[i][j]][image[i + di[k]][j + dj[k]]]++;
				numberOfElements++;
			}
		}
		double energy = 0;
		double constrast = 0;
		double homogeniety = 0;
		for(int i = 0; i < PIXEL_MAX; i++){
			for(int j = 0; j < PIXEL_MAX; j++){
				double probability = GLCM_matriz[i][j] / (numberOfElements);
				energy += probability * probability;
				constrast += (double)(abs(i - j) * abs(i - j)) * probability;
				homogeniety += probability / (double)(1.0 + abs(i - j));
			}
		}
		features[k * 3 + 0] = energy;
		features[k * 3 + 1] = constrast;
		features[k * 3 + 2] = homogeniety;
	}
	return features;
}

const int ROTATION_SIZE = 9;
const int ILBP_MATRIX = 1;

int rightShift(int original)
{
	int ret = 0;
	if(original & 1)
		ret += 1 << (ROTATION_SIZE - 1);
	for(int i = 1; i < ROTATION_SIZE; i++){
		if((1 << i) & original)
			ret += (1 << (i - 1));
	}
	return ret;
}

double * ILBP(int ** image)
{
	int ILBP_count[ILBP_SIZE];
	memset(ILBP_count, 0, sizeof ILBP_count);
	int bitmask, ILBP_codigo;
	double media;
	for(size_t i = ILBP_MATRIX; i < IMAGE_MATRIX_SIDE - ILBP_MATRIX; i++){
		for(size_t j = ILBP_MATRIX; j < IMAGE_MATRIX_SIDE - ILBP_MATRIX; j++){
			bitmask = 0;
			media = 0;
			for(int li = -ILBP_MATRIX; li <= ILBP_MATRIX; li++)
				for(int lj = -ILBP_MATRIX; lj <= ILBP_MATRIX; lj++)
					media += image[i + li][j + lj];
			media = media / (double)((ILBP_MATRIX * 2 + 1) * (ILBP_MATRIX * 2 + 1));
			for(int li = -ILBP_MATRIX; li <= ILBP_MATRIX; li++)
				for(int lj = -ILBP_MATRIX; lj <= ILBP_MATRIX; lj++)
					if(image[i + li][j + lj] >= media)
						bitmask = bitmask + (int)(1LL << ((lj + ILBP_MATRIX) + (li + ILBP_MATRIX) * (ILBP_MATRIX * 2 + 1)));
			ILBP_codigo = bitmask;
			for(int i = 0; i < ROTATION_SIZE; i++){
				int nova_bitmask = rightShift(bitmask);
				if(ILBP_codigo > nova_bitmask)
					ILBP_codigo = nova_bitmask;
				bitmask = nova_bitmask;
			}
			ILBP_count[ILBP_codigo]++;
		}
	}
	double * features = (double *) malloc(sizeof(double) * ILBP_SIZE);
	for(int i = 0; i < ILBP_SIZE; i++)
		features[i] = ILBP_count[i];
	return features;
}

int ** readFromDataset(char * datasetType, int datasetID)
{
	char filepath[1000];
	char id[5];

	sprintf(id, "%.2d", datasetID);

	filepath[0] = '\0';

	strcat(filepath, "resources/dataset/");
	strcat(filepath, datasetType);
	strcat(filepath, "/");
	strcat(filepath, datasetType);
	strcat(filepath, "_");
	strcat(filepath, id);
	strcat(filepath, ".txt");

	FILE * file = fopen(filepath, "r");

	if(file == NULL)
	{
		printf("[ERROR] Target file was not found, path: '%s'\n	Read file in resources/dataset for more information\n\n", filepath);
		fflush(stdout);
		exit(1);
	}
	else
	{
		printf("Loading %s\n", filepath);
		fflush(stdout);
	}
	
	
	int ** read = (int **) malloc(sizeof(int *) * IMAGE_MATRIX_SIDE);

	for(int i = 0; i < IMAGE_MATRIX_SIDE; i++)
	{
		read[i] = (int *) malloc(sizeof(int) * IMAGE_MATRIX_SIDE);
	}

	int i = 0, j = 0;

	while(!feof(file))
	{
		fscanf(file, "%d;", &read[i][j++]);

		if(j >= IMAGE_MATRIX_SIDE)
			i++, j = 0;
	}

	fclose(file);

	return read;
}

double * getFeaturesList(char * datasetType, int datasetID)
{
	fflush(stdout);
	int ** rawImage = readFromDataset(datasetType, datasetID);

	double * features = (double *) malloc(sizeof(double) * FEATURE_LIST_SIZE);
	double * featuresGLCM = GLCM(rawImage);
	double * featuresILBP = ILBP(rawImage);

	for(int i = 0; i < IMAGE_MATRIX_SIDE; i++)
	{
		free(rawImage[i]);
	}
	
	free(rawImage);

	memcpy(features, featuresILBP, sizeof(double) * ILBP_SIZE);
	memcpy(features + ILBP_SIZE, featuresGLCM, sizeof(double) * GLCM_SIZE);

	free(featuresGLCM);
	free(featuresILBP);	

	return features;
}

// Public

double ** getFeatures(char * datasetType, int datasetSize, int * datasetIDs)
{
	double ** allFeatures = (double **) malloc(sizeof(double *) * datasetSize);
	for(int i = 0; i < datasetSize; i++)
	{
		allFeatures[i] = getFeaturesList(datasetType, datasetIDs[i]);
	}
	return allFeatures;
}

int getFeatureListSize()
{
	return FEATURE_LIST_SIZE;
}

void permuteFeatures(double ** features, int featureListSize)
{
	for(int i = 0; i < featureListSize; i++)
	{
		int rindx = randInt(0, featureListSize - 1);
		double * temp = features[i];
		features[i] = features[rindx];
		features[rindx] = temp;
	}
}