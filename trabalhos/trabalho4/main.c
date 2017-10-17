/*

	Nome: Giovanni Attina do Nascimento
	N USP: 9286614


	A implementacao este trabalho segue as definicoes descritas no arquivo PDF presente no runcodes
*/

#include "functions.h"


#define recebe_linha(linha) {\
	fgets(linha, 1001, stdin);\
	if(linha[strlen(linha) -1] == '\n') linha[strlen(linha) -1] = '\0';\
	}

int main(){
	
	char linha[1001];
	int qnt = 0;
	infos *dados = malloc(sizeof(infos)*20);
	infos *aux;
	do{
		fgets(linha, 1001, stdin);
		if(linha[strlen(linha) -1] == '\n') linha[strlen(linha) -1] = '\0';
		
		//printf("%s\n", linha);
		//ve se e'um f utliza algoritomo fifo nos dados
		if(linha[0] == 'f'){

		 // rrecebe os dados como especificado para fifo  
		}else{//recebe utilizando 
			aux = recebe_dados(linha);
			dados[qnt++] = aux;
		}
		printf("oi\n");
	}while(!feof(stdin));

	return 0;
}