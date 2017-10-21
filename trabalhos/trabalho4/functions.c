
#include "functions.h"
#include "estrutura_dados/fila.h"
#include "estrutura_dados/linked_list.h"



void recebe_dados(char *linha, infos *dados){
	int r, pos, num, c, controle, check;
	pos = 0; controle = 0; check = 0;
	process *dado = malloc(sizeof(process));
	/*
		Controle -> Variavel para saber qual ponto salvar 	
	*/
	while ((r = sscanf(&linha[pos], "%d%n", &num, &c)) != EOF){//read all the line
	 // printf("%d %f %d\n", r, num, c);
		if (r == 1){//if is a digit
			switch(controle){
				case 0:
				//checa antes de adicionar numero do precoesso se ja um com o mesmo numero
				check =  checa_processo_nome(num, dados);
				if(check == 1) dado->p0 = num +1;
				else dado->p0 = num;
				
				case 1:
				dado->t00 = num;
				case 2:
				dado->tf0 = num;
				case 3:
				dado->r0 = num;
			}

			controle++;
	        pos += c;
	    }
	    if (r == 0) pos += c;//se achar um espaco
	        

	}
	dados->p[dados->qnt++] = dado;
	//printf("qnt : %d %d %d  %d \n",dados->qnt-1 ,dados->p[dados->qnt-1]->p0, dados->p[dados->qnt-1]->t00, dados->p[dados->qnt-1]->tf0);

}

int checa_processo_nome(int num, infos *dados){
	/*	
		Checa os numeros dos processados entrados e se já tiver um igual retorna 1
		Entrada:
			num-> numero para checar
			dados -> dados para olhar todos
		Saida:
			0 -> se nao tiver
			1 -> se tiver
	*/
	for(int i = 0; i < dados->qnt; i++){
		if(dados->p[i]->p0 == num){
			return 1;
		}
	}
	return 0;
}



void ordena_prioridade(infos *dados){

	process *aux;
	for(int i = 0; i < dados->qnt-1; i++){
		for(int j = 0; j < dados->qnt; j++){
			if(dados->p[i]->r0 > dados->p[j]->r0){
				aux = dados->p[i];
				dados->p[i] = dados->p[j];
				dados->p[j] = aux;
			}else if(dados->p[i]->r0 == dados->p[j]->r0){
				if(dados->p[i]->p0 > dados->p[j]->p0){
					aux = dados->p[i];
					dados->p[i] = dados->p[j];
					dados->p[j] = aux;
				}
			}
		}
	}

}

void print_process(infos *f){
	for(int i = 0; i < f->qnt; i++){
		printf("%d %d  %d \n", f->p[i]->p0, f->p[i]->t00, f->p[i]->tf0);
	}
}

void print_final(result *f, int qnt){
	for(int i = 0; i<qnt; i++){
		printf("%d %d \n", f[i].process, f[i].time);
	}
}

void adiciona_resultando(result *r, process *p, int time){
	r->process = p->p0;
	r->time = time;
}