//file to define the struct to save the dade and functions
#ifndef fila_H
#define fila_H

#include "../functions.h"


#define MAX 1000

typedef struct t_item_f t_item_f;

struct t_item_f{
	process *item;
};

typedef struct{
	int qnt;
	t_item_f itens[MAX];
}queue;

void cria(queue *q);
void  add_item_q(queue *q, process *item);
process *remove_item_q(queue *q);
result *recebe_processos(infos *processos);
void adiciona_processo_fila(infos *processos, queue *q, int quantum);
#endif