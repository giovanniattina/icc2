//#include "fila.h"
//#include "../functions.h"


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

queue *adiciona_item_fila(infos *dados){

	queue *q = malloc(sizeof(queue));

	cria(q);

	for(int i = 0; i< dados->qnt; i++){
		add_item_q(q, &dados[i]);
	}
	return q;
}