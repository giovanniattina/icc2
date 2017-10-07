/*
	Nome: Giovanni Attina do Nascimento
	NºUSP: 9286614

	Trabalho implementado com as instruções dadas no arquivo disponiveil no site 
	run codes
*/


#include "funcoes.h"


int main(){

	
	char *exp;//para receber a expressao
	exp = malloc(sizeof(char)*201);//aloca espaco para receber a expressao
	int lexico, i;//lexico -> para receber se tem erro ou nao
	//i-> conta a linha q esta lendo

	dados print;
	inicializa_dados(&print);

	i = 0;
	//recebe dados
	do{
		fgets(exp, 201, stdin);//recebe a linha
		if(exp[strlen(exp) -1] == '\n'){//tratar para tirar \n se tiver na string
			exp[strlen(exp) -1]= '\0';
		}

		lexico = analizador_lexico(exp, &print);//faz analize lexica e a sintatica ta embutida na sintatica
		
		if(lexico == 0){//se não tiver erro 
			//nao faz nada
		}else if(lexico == 1){//se nao contar como objeto
			printf("Error line %d \n", i+1);
			break;
		}
		i++;

	
	}while(!feof(stdin));//executa ate final do arquivo
	
	print_dados(&print);

	
	free(exp);
	return 0;
}