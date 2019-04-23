#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

double features_asfalto[536];
double features_grama[536];

char nomeDoArquivo[100];

int grama_treino[25], grama_teste[25], asfalto_treino[25], asfalto_teste[25];

char * tipoDeArquivo = ".txt";

int x = 1;

int randInt(int l, int r){

	if(l > r)
		return 0;

	x = (x * x + time(NULL)) % 1000;
	
	return rand() % (r - l + 1) + l;

}

void formarNome(char * tipo, int numero){

	int i = 0;

	for( ; i < strlen(tipo); i++)
		nomeDoArquivo[i] = tipo[i];

	nomeDoArquivo[i++] = '_';

	nomeDoArquivo[i++] = '0' + numero / 10;

	nomeDoArquivo[i++] = '0' + numero % 10;

	for(int j = 0; j < strlen(tipoDeArquivo); j++)
		nomeDoArquivo[i++] = tipoDeArquivo[j];

}

void separarTreinoTeste(int * array_treino, int * array_teste){

	bool processado[50];

	memset(processado, false, sizeof processado);

	int separados = 0;
	int teste = 0;
	int treino = 0;

	while(separados != 50){

		int novo = randInt(1, 50);

		if(processado[novo - 1])
			continue;

		processado[novo - 1] = 1;

		if(treino < 25)
			array_treino[treino++] = novo;

		else
			array_teste[teste++] = novo;

		separados++;

	}
}

void treinar(int * array_de_treino, char * nome){

	for(int i = 0; i < 25; i++){

		FILE * arquivo;

		formarNome(nome, array_de_treino[i]);

		printf("%s\n", nomeDoArquivo);

	}

}

double teste(){



}

int main(){

	separarTreinoTeste(grama_treino, grama_teste);

	separarTreinoTeste(asfalto_treino, asfalto_teste);

	treinar(grama_treino, "grass");

	treinar(asfalto_treino, "asphalt");

}