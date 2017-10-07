#ifndef FUNCOES_H
#define FUNCOES_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//estrutura para salvar a quantidade de cada item contabilizado
typedef struct {
	int object;
	int array;
	int pairs; 
	int strings;
	int numbers;
	int trues;
	int falses; 
	int nulls;
}dados;

int conta_token_terminais(dados *d, char *exp, int inicio, int fim);
int analiza_sintatico(char *exp, dados *d, int inicio, int fim);
int analizador_lexico(char *exp, dados *d);
void inicializa_dados(dados *d);
void print_dados(dados *d);
int analiza_token(dados *d, char *exp, int inicio, int fim);
int analizado_numero(dados *d, char *exp, int inicio, int fim);
#endif