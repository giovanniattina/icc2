
#include "functions.h"
#include "estrutura_dados/fila.h"
#include "estrutura_dados/linked_list.h"



void recebe_dados(char *linha, infos *dados){
	int r, pos, num, c, controle, check;
	pos = 0; controle = 0; check = 0;
	dados->qnt =0;
	infos dado;
	/*
		Controle -> Variavel para saber qual ponto salvar 	
	*/
	while ((r = sscanf(&linha[pos], "%d%n", &num, &c)) != EOF){//read all the line
	 // printf("%d %f %d\n", r, num, c);
		if (r == 1){//if is a digit
			printf("dado recebido%d\n", num);
			switch(controle){
				case 0:
				//checa antes de adicionar numero do precoesso se ja um com o mesmo numero
				check =  checa_processo_nome(num, dados);
				if(check == 1) dado.p.p0 = num +1;
				else dado.p.p0 = num;
				
				case 1:
				dado.p.t00 = num;
				case 2:
				dado.p.tf0 = num;
				case 3:
				dado.p.r0 = num;
			}

			controle++;
	        pos += c;
	    }
	    if (r == 0) pos += c;//se achar um espaco
	        
	}
	dados[dados->qnt++] = dado;

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
		if(dados[i].p.p0 == num){
			return 1;
		}
	}
	return 0;
}



void ordena_prioridade(infos *dados){

	infos aux;
	for(int i = 0; i < dados->qnt-1; i++){
		for(int j = 0; j < dados->qnt; j++){
			if(dados[i].p.r0 > dados[j].p.r0){
				aux = dados[i];
				dados[i] = dados[j];
				dados[j] = aux;
			}else if(dados[i].p.r0 == dados[j].p.r0){
				if(dados[i].p.p0 > dados[j].p.p0){
					aux = dados[i];
					dados[i] = dados[j];
					dados[j] = aux;
				}
			}
		}
	}

}

result *executa_processos(infos *dados){
	int quantum = 0;
	int aux_int, aux_qnt_final;
	t_list processos;
	infos *aux;
	result *final = malloc(sizeof(result)*dados->qnt);
	aux_qnt_final = 0;
	while(1){
		quantum++;
		if(processos.qnt > 0){
			for(int i = 0; i<processos.qnt; i++){
				aux = retira_qualquer_item(&processos, 1);
				if(aux->tf0 == 0){
					final[aux_qnt_final].process = aux.p0;
					final[aux_qnt_final].time = quantum;

				}else aux->tf0--;

			}
		}
		if((aux_int =novo_processo(quantum, infos *dados)) != -1){
			add_item(&processos, &dados[aux]);
		}
	}
}

int novo_processo(int q, infos *dados){
	for(int i = 0; i < dados->qnt; i++){
		if(dados[i].p.t00 = q){
			return i;
		} 
	}
	return -1;
}



