
#include "funcoes.h"

#define TAMANHO 1001
/*
 *	Recebe um ponteiro de char e pega o que esta no stdin e salva nele, tirando o \n do final
 *	@parametros ponteiro do char para salvar a string
 */
#define recebe_linha(linha) {\
	fgets(linha, 1001, stdin);\
	if(linha[strlen(linha) -1] == '\n') linha[strlen(linha) -1] = '\0';\
	}
int main(){

  char *entrada, **entradas;
	itens **dados;
  int qnt;

  entrada = (char*)malloc(sizeof(char)*TAMANHO);
  qnt = 1;
  entradas = (char**)malloc(sizeof(char*)*qnt);
  do{
    recebe_linha(entrada);
    entradas[qnt-1] = strdup(entrada);
		printf("entrada :%s\n", entradas[qnt-1]);

		qnt++;

    entradas = (char**)realloc(entradas, sizeof(char*)*qnt);
	}while(!feof(stdin));

	dados = separa_itens(entradas, qnt-1);

  return 0;
}
