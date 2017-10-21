/*

	Nome: Giovanni Attina do Nascimento
	N USP: 9286614


	A implementacao este trabalho segue as definicoes descritas no arquivo PDF presente no runcodes
*/

#include "functions.h"
#include "estrutura_dados/fila.h"


#define recebe_linha(linha) {\
	fgets(linha, 1001, stdin);\
	if(linha[strlen(linha) -1] == '\n') linha[strlen(linha) -1] = '\0';\
	}

int main(){
	
	char linha[1001];
	int qnt, tipo_entrada;
	qnt = 0;
	infos *dados = malloc(sizeof(infos));
	dados->p = malloc(sizeof(process)*20);
	dados->qnt = 0;
	result *f;
	do{
		fgets(linha, 1001, stdin);
		if(linha[strlen(linha) -1] == '\n') linha[strlen(linha) -1] = '\0';
		
		//printf("%s\n", linha);
		//ve se e'um f utliza algoritomo fifo nos dados
		if(qnt == 0 && linha[0] == 'f'){
			tipo_entrada = 0;
		}else if(qnt == 0)tipo_entrada = 1;
		
		if(linha[0] != 'f'){
			recebe_dados(linha,dados);
		}
		qnt++;
	}while(!feof(stdin));

	if(tipo_entrada == 1){
	}else{
		f = recebe_processos(dados);
	}
	print_final(f, dados->qnt);
	return 0;
}