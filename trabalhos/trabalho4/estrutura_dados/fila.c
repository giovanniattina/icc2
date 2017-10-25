#include "fila.h"
#include "../functions.h"


void cria(queue *q){
	q->qnt = 0;
}


void add_item_q(queue *q, process *item){
	
	if(q->qnt > MAX) exit(1);

	q->itens[q->qnt++].item = item;
}

process *remove_item_q(queue *q){

	process *aux;
	// aux -> para salvar o item q vai retornar
	aux = q->itens[0].item;
	q->qnt--;
	for(int i = 0; i < q->qnt; i++){//como tirou o primeiro item desloca o resto dos item para o comeco da fila
		q->itens[i] = q->itens[i+1];
	}
	return aux;
}



result *recebe_processos(infos *processos){
	int quantum, cont_aux;

	queue q;
	result *final = malloc(sizeof(result)*processos->qnt);
	process *p;
	/*
	 *	quantum -> variavel para controlar o tempo que os processos estao rodando
	 *	cont_aux -> variavel para contalar quntos processos ja acabaram de rodas
	 *	q -> para criar fila para colocar os processos que estao rodando
	 *	final -> para salvar os processos que acabaram e retorna-los ao usuario no final
	 *	p -> auxiliar para salvar um processo para analizar quando tira-lo da fila
	 */
	cria(&q);
	quantum = 0; 
	cont_aux = 0;


	do{	
		quantum++;
		adiciona_processo_fila(processos, &q, quantum);//se ve tem novos processos no quantum presente
		if(q.itens[0].item->tf0 > 0){//se se o processo no topo da fila ainda ta rodando
			q.itens[0].item->tf0--;
			if(q.itens[0].item->tf0 == 0){//se acabou o tempo do processo
				p = remove_item_q(&q);//retira ele da fila
				adiciona_resultando(&final[cont_aux++], p, quantum); //coloca nos processos acabados
			}
		}

	}while(q.qnt > 0);// roda em quanto tiver processo na fila

	

	return final;
}


void adiciona_processo_fila(infos *processos, queue *q, int quantum){
	process **aux = malloc(sizeof(*processos)*10);
	process *aux2;
	int auxC = 0;
	/*
	 *	aux -> cria um vetor para receber ponteiros dos processos para ser adicionado
	 *	aux2 -> para guarda um unico processo
	 *	auxC -> variavel para contar quantos processos vão ser salvo 
	 */
	for(int i = 0; i< processos->qnt; i++){//analiza todos os processos
		if(processos->p[i]->t00 == quantum){//se tiver processo novo no momento do quantum adiciona na fila
			aux[auxC++] = processos->p[i];
		}
	}

	//nos processos novos no determinando quantum ordena eles em ordem do id do processos
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
	
	free(aux);
}

