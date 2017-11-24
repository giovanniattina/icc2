
#include "funcoes.h"

#define TAMANHO 1001

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
  entradas = (char**)malloc(sizeof(char*)*100);

	qnt = 1;
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
