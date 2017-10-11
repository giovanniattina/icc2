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
	
	char line[1001];
	int qnt = 0;
	infos *dados = malloc(sizeof(dados)*20);
	do{
		recebe_linha(line);
		
		printf("%s\n", line);
		//ve se e'um f utliza algoritomo fifo nos dados
		if(line[0] == 'f'){

		 // rrecebe os dados como especificado para fifo  
		}else{//recebe utilizando 
			
			dados[qnt++] = recebe_dados(line);
		}
	}while(!feof(stdin));

	return 0;
}