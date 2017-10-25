/*

	Nome: Giovanni Attina do Nascimento
	N USP: 9286614


	A implementacao este trabalho segue as definicoes descritas no arquivo PDF presente no runcodes
*/

#include "functions.h"
#include "estrutura_dados/fila.h"
#include "estrutura_dados/linked_list.h"




int main(){
	
	char linha[1001];
	int qnt, tipo_entrada;
	infos *dados = malloc(sizeof(infos));
	result *f;
	/*
 	 *	qnt -> controla a quantidade de dados que entra
	 *	tipo_entrada -> se vai usar fila ou lista
	 *	dados -> todos os dados de entrada
	 *	f-> resultado do escalonamento
	 */

	qnt = 0;
	dados->p = malloc(sizeof(process)*20);
	dados->qnt = 0;
	do{
		recebe_linha(linha);
		
		if(qnt == 0 && linha[0] == 'f'){//se for usa fila
			tipo_entrada = 0;
		}else if(qnt == 0)tipo_entrada = 1;
		
		if(linha[0] != 'f'){//recebe os dados normal
			recebe_dados(linha,dados);
		}
		qnt++;
	}while(!feof(stdin));

	if(tipo_entrada == 1){
		f = recebe_processos_f(dados);
	}else{
		f = recebe_processos(dados);
	}
	print_final(f, dados->qnt);

	//libera memoria dinamica
	libera_dados(dados);
	free(f);

	return 0;
}