//file to define the struct to save the dade and functions
#ifndef fila_H
#define fila_H

#include "../functions.h"


#define MAX 1000

typedef struct t_item_f t_item_f;

struct t_item_f{
	infos *item;
};

typedef struct{
	int qnt;
	t_item_f itens[MAX];
}queue;

void cria(queue *q);
void  add_item_q(queue *q, infos *item);
infos *remove_item_q(queue *q);
queue *adiciona_item_fila(infos *dados);
int novo_processo(int q, infos *dados);
result *executa_processos(infos *dados);

#endif