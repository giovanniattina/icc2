//file to define the struct to save the dade and functions
#ifndef FUNCOES_H
#define FUNCOES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*
	Structure to save the data
	p0 -> indentification code
	t00 -> time to be recognize by the escalonator
	tf0 -> time to the process take to run
	r0 -> priorid*  of running 
*/
typedef struct{
	int p0, t00, tf0, r0;
}process;

typedef struct{
	process **p;
	int qnt;
}infos;


typedef struct{
	int process;
	int time;
}result;


	
void recebe_dados(char *linha, infos *dados);
void ordena_prioridade(infos *dados);
int checa_processo_nome(int num, infos *dados);
void print_final(result *f, int qnt);
void print_process(infos *f);
void adiciona_resultando(result *r, process *p, int time);

#endif