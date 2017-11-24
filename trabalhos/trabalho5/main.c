
#include "funcoes.h"

#define TAMANHO 1001
/*
 *	Recebe um ponteiro de char e pega o que esta no stdin e salva nele, tirando o \n do final
 *	@parametros ponteiro do char para salvar a string
 */
#define recebe_linha(linha) {\
	fgets(linha, TAMANHO, stdin);\
	if(linha[strlen(linha) -1] == '\n') linha[strlen(linha) -1] = '\0';\
	}
int main(){
	/**
	 * entrada -> recebe cada linha de entradas
	 * entradas -> salva todas as linhas de entrada
	 * t-> salva as informacoes do terminal
	 * e -> salva os tipos e as quantdade de erros de entradas
	 * qnt -> quantidade de operacoes entradas
	 * valor_auditoria -> onde comeca a ter operacoes da auditoria
	 */

	char *entrada, **entradas;
	itens **dados;
	terminal **t;
	erros *e;
  int qnt, valor_auditoria;

	e = (erros*)calloc(1, sizeof(erros));
	valor_auditoria = 0;
  entrada = (char*)malloc(sizeof(char)*TAMANHO);
  qnt = 1;
  entradas = (char**)malloc(sizeof(char*)*100);
  do{
    recebe_linha(entrada);
    entradas[qnt-1] = strdup(entrada);
			qnt++;

	}while(!feof(stdin));

	dados = separa_itens(entradas, qnt-1, e);
	t = processa_entrada(dados, qnt-1, &valor_auditoria);
	relatorio(t, e);
	if(valor_auditoria !=0) imprime_auditoria(valor_auditoria, qnt, dados, t);
	//libera memoria
	libera_entrada(qnt-1, entradas);
	libera_itens(qnt-1, dados);

	libera_terminal(t);
	free(e);
	free(entrada);
	exit(0);
  return 0;
}
