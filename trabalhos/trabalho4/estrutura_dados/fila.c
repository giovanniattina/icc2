#include "fila.h"
#include "../functions.h"


void cria(queue *q){
	q->qnt = 0;
}


void add_item_q(queue *q, process *item){
	
	if(q->qnt > MAX) exit(1);

	q->itens[q->qnt++].item = item;
}
void add_item_es(queue *q, process *item){
	t_item_f aux;
	if(q->qnt > 1){//ignora o primeiro item
		//insera ordenado 
		for(int i = 1; i < q->qnt; i++){
			if(item->p0 < q->itens[i].item->p0){
				aux = q->itens[i]; //salva item q sera redirecioando
				q->itens[i].item = item;//adiciona o novo item 
				q->qnt++;//aumenta uma possição para pode ser shifitado
				for(int j = q->qnt-1; j > i; j--){//shifita os itens
					q->itens[j+1] = q->itens[j];
				}
				q->itens[i+1] = aux;//salva 
				break;
			}else{
				q->itens[q->qnt++].item = item; break;
			}
			
		}
	}
	else{
		q->itens[q->qnt++].item = item; 
	}
}

process *remove_item_q(queue *q){

	process *aux;

	aux = q->itens[0].item;
	q->qnt--;
	for(int i = 0; i < q->qnt; i++){
		q->itens[i] = q->itens[i+1];
	}
	return aux;
}

//para o fifo
result *recebe_processos(infos *processos){
	int quantum, cont_aux;
	queue q;
	result *final = malloc(sizeof(result)*processos->qnt);
	process *p;
	cria(&q);
	/*
		quantum -> medida do tempo
	*/
	quantum = 0; 
	cont_aux = 0;


	do{	
		quantum++;
		adiciona_processo_fila(processos, &q, quantum);
		if(q.itens[0].item->tf0 > 0){
			q.itens[0].item->tf0--;
			if(q.itens[0].item->tf0 == 0){
				p = remove_item_q(&q);
				adiciona_resultando(&final[cont_aux++], p, quantum);
			}
		}

	}while(q.qnt > 0);

	

	return final;
}

void adiciona_processo_fila(infos *processos, queue *q, int quantum){
	process **aux = malloc(sizeof(*processos)*10);
	process *aux2;
	int auxC = 0;
	for(int i = 0; i< processos->qnt; i++){
		if(processos->p[i]->t00 == quantum){//se tiver processo novo no momento do quantum adiciona na fila
			aux[auxC++] = processos->p[i];
		}
	}

	//ordena lista
	for (int i = 0; i < auxC -1; ++i){
		for (int j = 1; j < auxC; ++j){
			if(aux[i]->p0 > aux[j]->p0){
				aux2 = aux[i];
				aux[i] = aux[j];
				aux[j] = aux2;
			}
		}
	}

	//passa da lista para a fila
	for (int i = 0; i < auxC; ++i){
		add_item_q(q, aux[i]);
	}
}

