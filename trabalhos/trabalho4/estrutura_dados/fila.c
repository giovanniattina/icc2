#include "fila.h"



void cria(queue *q){
	q->qnt = 0;
}


void add_item_q(queue *q, infos *item){
	
	if(q->qnt > MAX) exit(1);

	q->itens[q->qnt++].item = item;
}
infos *remove_item_q(queue *q){

	infos *aux;

	aux = q->itens[0].item;
	q->qnt--;
	for(int i = 0; i < q->qnt; i++){
		q->itens[i] = q->itens[i+1];
	}
	return aux;
}