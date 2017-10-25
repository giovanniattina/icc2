#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdio.h>
#include <stdlib.h>
#include "../functions.h"


#define MAX 1000 // quantidade maxima de itens em uma fila

//representa um item da lista
typedef struct t_item t_item;

//definicao do item da lista
struct t_item{
	process *d;
};

//estrutura para salvar a quantidade e todos itens de uma lista
typedef struct {
	int qnt;
	t_item L[MAX];
}t_list;

/*
 *	Funcao recebe uma lista e seta a quantidade de itens para 0
 *	@parametros lista a ser setada
 */
void create_list(t_list *l);

/*
 *	Funcao retira um item q qualquer possicao da fila
 *	@parametros lista a ser tirada o item e posicao para tirar o item
 */
process *retira_qualquer_item(t_list *t, int pos);

/*
 *	Funca recebe um item e coloca ordenado na lista por ordem de prioridade do processo
 *	@parametros lista que coloca o item e item que sera colocado
 */
result *recebe_processos_f(infos *dados);

/*
 *	Adiciona um item na lista em qualquer possição
 *	@parametros Lista que adicionara o item, posicao que o item sera adicionado e item que sera adicionado
 */
void adiciona_qualquer_lugar(t_list *t, int pos, process *item);

/*
 * 	Funcao adiciona os novos processos de um determinado tempo na lista
 *	@parametros lista que os novos processos sera adicionado, dados da onde retirara o processo e tempo para entrar os novos processos
 *	@retorno 1 se tiver ainda que executar todos os processos de uma prioridade e 0 se nao
 */
int adiciona_processos_lista(t_list *processos, infos *dados, int ultimo, int time, int *atual);

/*
 * Ordenada dos os itens da lista por prioridade do processo
 * @parametros lista com os processos para ordenar
 */
void ordena(t_list *processos);

/*
 *	Adiciona um item no final da lista 
 *	@parametros lista para adicionar item, item para adicionar 
 */
void adiciona(t_list *t, process *p);

#endif
