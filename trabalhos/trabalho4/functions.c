
#include "functions.h"
#include "estrutura_dados/fila.h"
#include "estrutura_dados/linked_list.h"



void recebe_dados(char *linha, infos *dados){
	int r, pos, num, c, controle, check;
	pos = 0; controle = 0; check = 0;
	process *dado = malloc(sizeof(process));
	/*
	 *	r -> para salvar retorno do sscanf, se acho um inteiro
	 *	pos -> controlar a pos na string de leitura
	 * 	num -> salvar o numero lid
	 *	c -> salvar o numero de byts contato em cada interacao
	 *	check -> para saber se já tem processo com o mesmo nome 
	 *	controle -> Variavel para saber qual ponto salvar 	
	 *	dado -> salvar o resultado da leitura
	*/
	while ((r = sscanf(&linha[pos], "%d%n", &num, &c)) != EOF){//read all the line
		if (r == 1){//se e um digito
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
	    }
	    pos += c;//se achar um espaco
	        

	}
	dados->p[dados->qnt++] = dado;
}

int checa_processo_nome(int num, infos *dados){

	for(int i = 0; i < dados->qnt; i++){//anda por todos os dados
		if(dados->p[i]->p0 == num){
			return 1;//se achar um nome igual
		}
	}

	return 0;
}


void print_final(result *f, int qnt){
	for(int i = 0; i<qnt; i++){//anda por todos os processos acabos
		printf("%d %d \n", f[i].process, f[i].time);
	}
}

void adiciona_resultando(result *r, process *p, int time){
	r->process = p->p0;
	r->time = time;
}