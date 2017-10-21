//file to define the struct to save the dade and functions
#ifndef FUNCOES_H
#define FUNCOES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*
 *	Structure to save the data
 *	p0 -> indentification code
 *	t00 -> time to be recognize by the escalonator
 *	tf0 -> time to the process take to run
 *	r0 -> priorid*  of running 
 */
typedef struct{
	int p0, t00, tf0, r0;
}process;

/*
 *	p -> para salvar o endereco de todos os processos
 *	qnt -> qtn de processos salvos	
 */
typedef struct{
	process **p;
	int qnt;
}infos;

/*
 *	process -> para salvar o id do processo
 *  time -> para salvar o quantum que o processo acabo
 */
typedef struct{
	int process;
	int time;
}result;


/* 
 *	Funcao para ler a string recebi e salvar nos dados
 *	@parametros linha com os dados de entrada, local para salvar os dados
 */	
void recebe_dados(char *linha, infos *dados);


void ordena_prioridade(infos *dados);

/*
 *	Checa se ja ha um processo com o mesmo nome, se sim retorna ao usuario
 *	@parametros id do processo novo, dados para checar todos os processos 
 *	@return 1 se tiver processo com o mesmo nome e 0 se nao tiver 
 */
int checa_processo_nome(int num, infos *dados);

void print_process(infos *f);

/*
 *	Adiciona um processo acabado nos resultados
 *	@parametros lista com processos acabado, processo acabado, tempo que o processo acabo	
*/
void adiciona_resultando(result *r, process *p, int time);
/*
 *	Retorna no stdout os id dos processos acabados e o tempo
 *	@parametros listas com os processos acabados e quantidade de processos
 */
void print_final(result *f, int qnt);

#endif