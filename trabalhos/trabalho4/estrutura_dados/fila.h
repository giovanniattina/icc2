//file to define the struct to save the dade and functions
#ifndef fila_H
#define fila_H


#include "../functions.h"

#define MAX 1000

typedef struct t_item t_item;

struct  t_item{
	infos *item;
};

typedef struct{
	int qnt;
	t_item itens[MAX];
}queue;

void cria(queue *q);
void  add_item_q(queue *q, infos *item);
infos *remove_item_q(queue *q);

#endif