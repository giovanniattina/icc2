//file to define the struct to save the dade and functions
#ifndef fila_H
#define fila_H

#include "../functions.h"


#define MAX 1000 // quantidade maxima de itens na fila
// item da fila
typedef struct t_item_f t_item_f;
// o vai ser salvo dentro da fila 
struct t_item_f{
	process *item;
};
//definicao da fila 
typedef struct{
	int qnt;
	t_item_f itens[MAX];
}queue;

/*
 *	Funcao seta a quantidade de dados em uma fila para 0
 *	@parametros fila para setar para 0
 */
void cria(queue *q);

/*
 *	Funcao adiociona um item na pilha
 *	@parametros q fila para adicionar item, item a ser adicionado	
 */
void  add_item_q(queue *q, process *item);

/*
 *	Funcao remove o primeiro item adicionado na fila
 *	@parametros fila para tirar item
 *	@return item retirando
 */
process *remove_item_q(queue *q);

/*	
 *	Funcao faz a simulacao do escalonado de processos
 *
 *	@parametros informacoes dos processos entrados
 *	@return informacoes com os ids dos processos e a quantidade de quantum que cada um levou para rodar
 */
result *recebe_processos(infos *processos);

/*
 *	Ve quais processos podem ser adiciona na fila em um determinando quantum
 *	@parametros todos os processos de entrada, fila para adicionar os novos processos, tempo que esta presente
 */
void adiciona_processo_fila(infos *processos, queue *q, int quantum);



#endif