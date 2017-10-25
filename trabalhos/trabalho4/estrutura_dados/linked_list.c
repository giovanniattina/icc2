#include "linked_list.h"


void create_list(t_list *l){

	l->qnt = 0;

}

void print_list(t_list *t){

	printf("lista\n");
	for (int i = 0; i < t->qnt; ++i){
		printf("%d ", t->L[i].d->p0);
	}
	printf("\n");
}

void adiciona(t_list *t, process *p){
	t_item aux;
	aux.d = p;

	t->L[t->qnt++] = aux;// adiciona um item no final da fila
}
void adiciona_qualquer_lugar(t_list *t, int pos, process *item){

	t_item aux;
	aux.d = item; //novo item

	for(int i = t->qnt+1; i > pos; i--)	t->L[i] = t->L[i-1];		

	t->qnt++;
	t->L[pos] = aux;
}

process *retira_qualquer_item(t_list *t, int pos){

	t_item ret = t->L[pos];//salva o item que vai retirar

	for (int i = pos; i < t->qnt; ++i){//shifita toda a lista para esquerda
		t->L[i] = t->L[i+1];
	}
	t->qnt--;

	return ret.d;
}


result *recebe_processos_f(infos *dados){

	int quantum, qnt_f, item_anal, salva_prioridade, auxI, controle;
	t_list processos;
	result *final = malloc(sizeof(result)*dados->qnt);
	process *aux;
	/*
	*	quantum -> variavel para contar o tempo
	*	qnt_f -> controlar quantidade de itens na fila
	*	final -> para salvar os processos que acabaram
	*	aux -> utilizar para salvar um processos temporariamente
	*	auxI -> variavel para saber quando estou em uma prioridade e entrou uma maior e tenho que acabar os processos de prioridade menor antes
	* 	controle -> para saber se tem q voltar para a prioridade mais alta, ativada quando auxI e ativada
	*/
	create_list(&processos);
	controle = 0;
	qnt_f = 0; quantum = 0; item_anal = 0; salva_prioridade = 0;
	do{//executa em quanto tiver item na lista
		quantum++;
		auxI =  adiciona_processos_lista(&processos, dados, salva_prioridade ,quantum, &item_anal);
		
		if(controle == 1){//se tiver que voltar para a prioridade mais alta
			item_anal = 0;
			controle = 0;
		}

		if (auxI == 1){//para executar ultimo processo de prioridade mais baixa antes de voltar apra a mais alta
			item_anal++;
			controle = 1;
		} 
		
		aux = processos.L[item_anal].d;
		aux->tf0--;
		if(aux->tf0 > 0){//se o processo tiver q executa ainda adiciona no final da lista
			//se o processo tiver prioridde 0, volta ele para o comeco da lista
			if(aux->r0 == 0){
				//não mudo meu item_analizado
			}else{
				item_anal++;	
			} 
		}else if(aux->tf0 == 0){// se nao adiciona na lista de processos acabados
			aux = retira_qualquer_item(&processos, item_anal);
			salva_prioridade = aux->r0;
			adiciona_resultando(&final[qnt_f++], aux, quantum);
		}
		if(item_anal == processos.qnt) item_anal = 0;//se chego no ultimo item volta para o comeco

	}while(processos.qnt > 0);
	return final;
}

int adiciona_processos_lista(t_list *processos, infos *dados, int ultimo, int time, int *atual){
	int retorna = 0, acho_0= 0;
	for(int i = 0; i < dados->qnt; i++){//olh sobre todos os processos
		if(dados->p[i]->t00 == time){
			//se achar um processo de prioridade 0 coloca no começo da lista
			if(dados->p[i]->r0 == 0){
				adiciona_qualquer_lugar(processos, 0, dados->p[i]);
				acho_0 = 1;
			}else{
				if(processos->qnt > 2 && (processos->L[*atual].d->r0 != 0) ){//se eu entrar um item de alta prioridade mas~ainda tiver item na prioridade que estou e o item que esta para executar nao pode ter prioridade 0
					if(dados->p[i]->r0 > processos->L[*atual].d->r0){//se novo processo e de prioridade do proximo executar
						if((processos->L[*atual].d->r0 != processos->L[*atual +1].d->r0)){//se o proximo processo não for na mesma prioridade volto para a mior prioridade
							
							if(processos->L[*atual].d->r0 == ultimo) retorna = 1;
							else *atual = 0;
						}
					}			
					
				}
				adiciona(processos, dados->p[i]);//adiciona um processo 

				ordena(processos);//ordena a lista toda
			}
		}
	}
	if(retorna == 1 && acho_0 != 1){
		return 1;
	} 
	return 0;
	
}

void ordena(t_list *processos){
	t_item aux;
	//utiliza um bubble sort para ordena a lista
	for (int i = 0; i < processos->qnt-1; ++i){
		for (int j = i; j < processos->qnt; ++j){
			if(processos->L[i].d->r0 != 0){
				if(processos->L[i].d->r0 < processos->L[j].d->r0){
					// faz a troca dos itens
					aux = processos->L[i];
					processos->L[i] = processos->L[j];
					processos->L[j] = aux;
				}else if(processos->L[i].d->r0 == processos->L[j].d->r0){
					if(processos->L[i].d->p0 > processos->L[j].d->p0){
						// faz a troca dos itens
						aux = processos->L[i];
						processos->L[i] = processos->L[j];
						processos->L[j] = aux;
					}
				}				
			}
		}
	}
}