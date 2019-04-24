#include <stdio.h> 		// printf
#include <stdlib.h>		// abs, rand, srand
#include <stdbool.h>	// bool
#include <time.h>		// time
#include <string.h>		// memset
#include <math.h> 		// fabs

#define TAMANHO_LEITURA 1025
#define TAMANHO_FEATURES 536
#define TAMANHO_DATASET 50
#define TAMANHO_ILBP 512
#define PIXEL_MAX 256
#define DIRECOES 8

double taxa_de_acerto = 0;
double falsa_aceitacao = 0;
double falsa_rejeicao = 0;

// As oito direcoes do GLCM

int di[] = {-1, -1, -1,  0,  0,  1,  1,  1};
int dj[] = {-1,  0,  1, -1,  1, -1,  0,  1};

// Array de features normalizadas

double norm_asfalto[TAMANHO_FEATURES];
double norm_grama[TAMANHO_FEATURES];

// Separa os indices de arquivos de treino e teste

int grama_treino[TAMANHO_DATASET/2], 
	grama_teste[TAMANHO_DATASET/2], 
	asfalto_treino[TAMANHO_DATASET/2], 
	asfalto_teste[TAMANHO_DATASET/2];

// Guarda leitura de imagem

int leitura[TAMANHO_LEITURA][TAMANHO_LEITURA];

char nomeDoArquivo[100];
char * nomeDaPasta = "./DataSet/";
char * tipoDeArquivo = ".txt";

unsigned int x = 1;

int randInt(int l, int r){

	// Para tornar retorno menos previsivel

	x = (x / 2 * x - x * x * 2 + x * 3 + 2 + time(NULL) - time(NULL) * x) % 
		((x * x * (time(NULL) * x++ + 3)) % 10000 + 100000);
	
	srand(x++);

	return rand() % (r - l + 1) + l;

}

// Para debugar e dar uma olhada na leitura de arquivos
void peekBidimensional(int size, int ** array){

	printf("\n");
	printf("-----------------\n");
	printf("\n");

	for(int i = 0; i < size; i++){
		printf("    ");
		for(int j = 0; j < size; j++){
			printf("%.4d ",array[i][j]);
		}
		printf("\n");
	}

	printf("\n");
	printf("-----------------\n");
	printf("\n");

}

// Para debugar e dar uma olhada nos features
void peek(int size, double * array){

	printf("\n");
	printf("-----------------\n");
	printf("\n");

	printf("    ");
	for(int i = 0; i < size; i++){
		printf("%.4lf ",array[i]);
	}
	printf("\n");

	printf("\n");
	printf("-----------------\n");
	printf("\n");

}

// Separa em dois conjuntos disuntos de mesmo tamanho o dataset para cada tipo do classificador
void separarTreinoTeste(int * array_treino, int * array_teste){

	bool processado[TAMANHO_DATASET];

	memset(processado, false, sizeof processado);

	int separados = 0;

	size_t teste = 0;
	size_t treino = 0;

	int novo;

	while(separados < TAMANHO_DATASET){

		if(processado[(novo = randInt(1, 50)) - 1])
			continue;

		processado[novo - 1] = 1;

		if(treino < TAMANHO_DATASET/2)
			array_treino[treino++] = novo;

		else
			array_teste[teste++] = novo;

		separados++;

	}
}

// Formata string de nome do arquivo
void formarNome(char * tipo, int numero){

	int i = 0;

	for( ; i < strlen(nomeDaPasta); i++)
		nomeDoArquivo[i] = nomeDaPasta[i];

	for(size_t j = 0; j < strlen(tipo); j++)
		nomeDoArquivo[i++] = tipo[j];

	nomeDoArquivo[i++] = '/';

	for(size_t j = 0; j < strlen(tipo); j++)
		nomeDoArquivo[i++] = tipo[j];

	nomeDoArquivo[i++] = '_';

	nomeDoArquivo[i++] = '0' + numero / 10;

	nomeDoArquivo[i++] = '0' + numero % 10;

	for(size_t j = 0; j < strlen(tipoDeArquivo); j++)
		nomeDoArquivo[i++] = tipoDeArquivo[j];

	nomeDoArquivo[i++] = '\0';

}

// Abre o arquivo e preenche array leitura com seu conteudo
bool ler(){

	FILE * arquivo;

	arquivo = fopen(nomeDoArquivo, "r");

	if(arquivo == NULL)
		return true;
		
	size_t v1 = 0, v2 = 0;

	while(fscanf(arquivo, "%d;", &leitura[v1][v2 = (v2 + 1) % TAMANHO_LEITURA]) != EOF){

		if(!v2)
			v1++;

	}

	fclose(arquivo);

	return false;

}

// Right shift binario com o detalhe de que se o primeiro bit for 1, ele vai para a nona casa
int rightShift(int original){

	int resultado = 0;

	if(original & 1)
		resultado += 1 << 9;

	for(int i = 1; i < 9; i++){

		if((1 << i) & original)
			resultado += (1 << (i - 1));

	}

	return resultado;

}

// Funcoes que auxiliam a funcao acumular
bool maiorQue(double a, double b){
	
	return a > b;

}

bool menorQue(double a, double b){

	return a < b;

}

// Faz passada linear na array aplicando funcao f
int acumular(double * array, bool (*f)(double, double), int tamanho){

	double valorMaximo = array[0];

	for(int i = 1; i < tamanho; i++){

		if(f(array[i], valorMaximo))
			valorMaximo = array[i];

	}

	return valorMaximo;

}

// Algoritmo de ILBP
void ILBP(double * features){

	int ILBP_resultado[TAMANHO_ILBP];

	memset(ILBP_resultado, 0, sizeof ILBP_resultado);

	int bitmask, ILBP_codigo;
	double media;

	for(size_t i = 1; i < TAMANHO_LEITURA - 1; i++){

		for(size_t j = 1; j < TAMANHO_LEITURA - 1; j++){

			bitmask = 0;
			media = 0;

			for(int li = -1; li <= 1; li++)
				for(int lj = -1; lj <= 1; lj++)
					media += leitura[i + li][j + lj];

			media = media / 9.0;

			for(int li = -1; li <= 1; li++)
				for(int lj = -1; lj <= 1; lj++)
					if(leitura[i + li][j + lj] > media)
						bitmask = bitmask + (1 << ((lj + 1) + (li + 1) * 3));

			ILBP_codigo = bitmask;

			for(int i = 0; i < 9; i++){

				int nova_bitmask = rightShift(bitmask);
				
				if(ILBP_codigo > nova_bitmask)
					ILBP_codigo = nova_bitmask;

				bitmask = nova_bitmask;

			}

			ILBP_resultado[ILBP_codigo]++;

		}

	}

	for(int i = 0; i < TAMANHO_ILBP; i++)
		features[i] = ILBP_resultado[i];

}

// Algoritmo de GLCM
void GLCM(double * features){

	double GLCM_matriz[PIXEL_MAX][PIXEL_MAX];

	double output[3 * 8];

	for(int k = 0; k < DIRECOES; k++){

		memset(GLCM_matriz, 0.0, sizeof GLCM_matriz);

		double numero_de_elementos = 0;

		for(int i = (di[k] == -1 ? 1 : 0); i < TAMANHO_LEITURA - (di[k] == 1 ? 1 : 0); i++){

			for(int j = (dj[k] == -1 ? 1 : 0); j < TAMANHO_LEITURA - (dj[k] == 1 ? 1 : 0); j++){

				GLCM_matriz[leitura[i][j]][leitura[i + di[k]][j + dj[k]]]++;

				numero_de_elementos++;
			
			}

		}

		double energia = 0;
		double contraste = 0;
		double homogeniedade = 0;

		for(int i = 0; i < PIXEL_MAX; i++){

			for(int j = 0; j < PIXEL_MAX; j++){

				double probabilidade = GLCM_matriz[i][j] / (numero_de_elementos);

				energia += probabilidade * probabilidade;

				contraste += (double)(abs(i - j) * abs(i - j)) * probabilidade;

				homogeniedade += probabilidade / (double)(1.0 + abs(i - j));
			
			}

		}

		features[TAMANHO_ILBP + k * 3 + 0] = energia;
		features[TAMANHO_ILBP + k * 3 + 1] = contraste;
		features[TAMANHO_ILBP + k * 3 + 2] = homogeniedade;

	}

}

// Normaliza array
void normalizar(double * array, double tamanho){

	for(int i = 0; i < TAMANHO_FEATURES; i++)
		array[i] /= (double)(tamanho);

	double maximo = acumular(array, maiorQue, TAMANHO_FEATURES);
	double minimo = acumular(array, menorQue, TAMANHO_FEATURES);

	for(int i = 0; i < TAMANHO_FEATURES; i++)
		array[i] = (array[i] - minimo) / (maximo - minimo);

}

// Treina um tipo para o classificador
bool treinar(int * array_de_treino, double * array_de_features, char * tipo){

	memset(array_de_features, 0.0, sizeof array_de_features);

	double features[TAMANHO_DATASET/2][TAMANHO_FEATURES];

	for(size_t i = 0; i < TAMANHO_DATASET/2; i++){

		printf(" - Arquivo %d de %s...\n", array_de_treino[i], tipo);

		formarNome(tipo, array_de_treino[i]);

		if(ler())
			return true;

		ILBP(features[i]);

		GLCM(features[i]);

	}

	for(int j = 0; j < TAMANHO_FEATURES; j++)
		for(int i = 0; i < TAMANHO_DATASET/2; i++)
			array_de_features[j] += features[i][j];

	normalizar(array_de_features, TAMANHO_DATASET/2);

	return false;

}

// Retorna distancia euclidiana entre dois vetores AO QUADRADADO pois cumpre a mesma funcao e evita usa pow, que e uma funcao terrivel
double distanciaEuclidiana(double * vetor1, double * vetor2){

	double distancia = 0;

	for(int i = 0; i < TAMANHO_FEATURES; i++){

		distancia += fabs(vetor1[i] - vetor2[i]) * fabs(vetor1[i] - vetor2[i]);

	}

	return distancia;

}

bool testar(int * array_de_teste, char * tipo){

	for(int i = 0; i < TAMANHO_DATASET/2; i++){

		double features[TAMANHO_FEATURES];

		formarNome(tipo, array_de_teste[i]);

		if(ler())
			return true;

		ILBP(features);

		GLCM(features);

		normalizar(features, 1);

		double distanciaGrama = distanciaEuclidiana(features, norm_asfalto);

		double distanciaAsfalto = distanciaEuclidiana(features, norm_grama);

		printf(" - Arquivo %d de %s: ", array_de_teste[i], tipo);

		if(distanciaAsfalto > distanciaGrama){

			if(tipo == "grass"){

				falsa_rejeicao++;
				printf("Falsa rejeicao");

			}else{ 

				taxa_de_acerto++;
				printf("Acerto");

			}

		}else{

			if(tipo == "asphalt"){

				falsa_aceitacao++;
				printf("Falsa aceitacao");

			}else{ 

				taxa_de_acerto++;
				printf("Acerto");
			}

		}

		printf("\n");

	}

	return false;

}

void lerLog(){

	FILE * arquivo;

	arquivo = fopen("./log.log", "r");

	double acc_acertos = 0, acc_falsa_rejeicao = 0, acc_falsa_aceitacao = 0, contagem = 0;
	double acertos, falsa_rejeicao, falsa_aceitacao;

	while(fscanf(arquivo, "%lf %lf %lf", &acertos, &falsa_rejeicao, &falsa_aceitacao) != EOF){

		acc_acertos += acertos;

		acc_falsa_aceitacao += falsa_aceitacao;

		acc_falsa_rejeicao += falsa_rejeicao;

		contagem++;

	}

	fclose(arquivo);

	acc_acertos /= contagem;
	acc_falsa_aceitacao /= contagem;
	acc_falsa_rejeicao /= contagem;

	acc_acertos *= 100.0;
	acc_falsa_aceitacao *= 100.0;
	acc_falsa_rejeicao *= 100.0;

	printf("▶ Acertos: %.2lf%% Falsa Rejeicao: %.2lf%% Falsa Aceitacao: %.2lf%%\n", acc_acertos, acc_falsa_rejeicao, acc_falsa_aceitacao);

}

void inserirLog(double acertos, double falsa_aceitacoes, double falsa_rejeicoes){

	FILE * arquivo;

	arquivo = fopen("./log.log", "a");

	fprintf(arquivo, "\n%.5lf %.5lf %.5lf", acertos, falsa_rejeicoes, falsa_aceitacoes);

	fclose(arquivo);

}

int main(){

	printf("\n▶ Separando dataset aleatoriamente...\n");

	separarTreinoTeste(grama_treino, grama_teste);

	separarTreinoTeste(asfalto_treino, asfalto_teste);

	printf("\n▶ Treinando 'grass'...\n\n");

	if(treinar(grama_treino, norm_grama, "grass")){

		printf("ERRO: \tHouve um problema na leitura de arquivos\n");
		printf("	  \tPor favor reinicie o programa\n");
		exit(1);

	}

	printf("\n▶ Treinando 'asphalt'...\n\n");

	if(treinar(asfalto_treino, norm_asfalto, "asphalt")){

		printf("ERRO: \tHouve um problema na leitura de arquivos\n");
		printf("	  \tPor favor reinicie o programa\n");
		exit(1);

	}

	printf("\n▶ Conjunto de treinamento pronto\n  Testando 'grass'...\n\n");

	if(testar(grama_teste, "grass")){

		printf("ERRO: \tHouve um problema na leitura de arquivos\n");
		printf("	  \tPor favor reinicie o programa\n");
		exit(1);

	}

	printf("\n▶ Testando 'asphalt'...\n\n");

	if(testar(asfalto_teste, "asphalt")){

		printf("ERRO: \tHouve um problema na leitura de arquivos\n");
		printf("	  \tPor favor reinicie o programa\n");
		exit(1);

	}

	printf("\n\n");

	taxa_de_acerto /= TAMANHO_DATASET;
	falsa_aceitacao /= TAMANHO_DATASET/2;
	falsa_rejeicao /= TAMANHO_DATASET/2;

	printf("▶ Taxa de acerto: %.2lf%%\n\n", taxa_de_acerto * 100.0);
	printf("▶ Taxa de falsa aceitacao: %.2lf%%\n\n", falsa_aceitacao * 100.0);
	printf("▶ Taxa de falsa rejeicao: %.2lf%%\n\n", falsa_rejeicao * 100.0);

	inserirLog(taxa_de_acerto, falsa_rejeicao, falsa_aceitacao);

	printf("\n▶ Log de execucoes anteriores:\n\n");

	lerLog();

	printf("\n\n");

}


