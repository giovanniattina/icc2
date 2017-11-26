#ifndef FUNCOES_H
#define FUNCOES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//utilizado para dar um valor a um item da estrutura itens quando nao precisa dele e para saber se e uma operacao de auditoria
#define SENTINELA -100.0
//numero maximo de terminal utilizados
#define MAX_TERMINAL 4

/**
 * [recebe_linha Recebe um ponteiro de char e pega o que esta no stdin e salva nele, tirando o \n do final]
 * @param  linha [ponteiro do char para salvar a string]
 * @return       [entrada do stdin]
 */
#define recebe_linha(linha) {\
	fgets(linha, TAMANHO, stdin);\
	if(linha[strlen(linha) -1] == '\n') linha[strlen(linha) -1] = '\0';\
	}


//salva os item de entrada para executar as operacoes de cada banco em cada terminal
typedef struct{

  float item1, item2, item3, item4;
  char *o;
}itens;

//estrutura utilizada para salvar quantidade de dinheiro transitado por cada banco em cada terminal
typedef struct{
    int id;
    float saque, deposito, transferencia_entrou, transferencia_saiu;
}banco;

//estrutua para contabilizar as operacoes que tiver erro na simulacao
typedef struct{
  int saque, transferencia, deposito, consulta, erro;
}erros;


/**
 * [estrutura para salvar as informacoes de cada terminal individualmente]
 * lucro [salvo o luro daquele terminal]
 * operacoes [salva todos as operacoes acessadas naquele terminal]
 * qnt_bancos [a quantidade de operacoes salvadas neste terminal]
 * bancos [salva as informacoes de cada banco, sendo que da um tem quatidade de dinheiro transitado por ele]
 * qnt_bancos [ quantidade de bancos acessados por o terminal]
 * id_bancos [numero dos bancos que foi acessado no terminal]
 * e [salva erros ocorridos no terminal]
 */
typedef struct{
    float lucro;
    itens **operacoes;
    int qnt_operacoes;
    banco **bancos;
    int qnt_bancos, *id_bancos;
		erros *e;
}terminal;
/**
 * [salva todos os bancos usados em todos os terminais]
 *[i_bancos salva as informacoes de todos os bancos usados em todos os terminais]
 *[ quantidade de bancos usando em todos os terminais]
 */
typedef struct{
  banco *i_bancos;
  int qnt;
}banco_final;


/**
 * [separa_itens pega as informacoes de entrada que esta em uma string e passa corretamenta para os bancos da struct item]
 * @param  entradas   [matriz com os dados de entrada]
 * @param  quantidade [quanidade de itens de entrada]
 * @return            [retorna um matriz como todos os dados separados]
 */
itens **separa_itens(char **entradas, int quantidade);

/**
 * [processa_entrada realiza cada operacao entrada pelos terminais]
 * @param  entradas [informacoes de entrada]
 * @param auditoria [quando chegar nas entrada de auditoria para de realizar os dados de entrada e salvo em qual item come a auditoria]
 * @param qnt [quantidade dados de entra]
 * @return          [dados separado em cada terminal]
 */
terminal **processa_entrada(itens **entradas, int qnt, int *auditoria);


/**
 * [passa_para_terminal pega um operacao e salva em um terminal especifico ]
 * @param operacao [operacao para salvar]
 * @param t        [temminal para salvar a operacao]
 */
void passa_para_terminal(itens *operacao, terminal *t);

/**
 * [processa_erro quando acha um ERRO salva a operacao na estrutura para contar os erros]
 * @param c [tipo da operacao que deu erro]
 * @param e [estrutura para salvar os erros]
 */
void processa_erro(char *c, erros *e);

/**
 * [hash recebe o numero da conta e o terminal que esta e calcular um valor de hash, usa o resto da divisão de um numero prim para cada
 * terminal e o numero da conta para calcular, RESULTADO: banco=r(mod terminal)]
 * @param  terminal [terminal que esta acessando]
 * @param  banco    [numero da conta que estou acessado]
 * @return          [numero de hash calculado]
 */
int hash(int terminal, int banco);

/**
 * [novo_espaco aloca um novo espaco para estrutura banco]
 * @return [um espaco para a estrutura banco alocadado na memoria heap]
 */
banco *novo_espaco();

/**
 * [salva_nova_operacao_banco recebe os dados de uma operacao e salva na estrutua banco]
 * @param operacao [operacao para salvar]
 * @param b        [endereco na memorida do banco para salvar a operacao]
 * @return [quando a operacao envolve dois bancos, como transferencia, retorna 1 para poder creditar o valor no outro banco
 * e retorna 0 quando a operacao nao envolve dois bancos]
 */
int salva_nova_operacao_banco(itens *operacao, banco *b);

/**
 * [relatorio mostra ao usuario um relatorio com as quatidade de dinheiro movimentada de cada terminal durante o dia e os erros acontecidos]
 * @param t [informacoes das operacoes acontecidas em cada terminal]
 */
void relatorio(terminal **t);

/**
 * [mostra_info_banco recebe as informacoes realizada em um banco em um determinando terminal e mostra no STDOUT]
 * @param b [informacoes a mostrar]
 */
void mostra_info_banco(banco *b);

/**
 * [salva_final pega as informacoes de cada banco e cada terminal e concentra todas as informacoes de cada banco para mostrar o total de cada banco]
 * @param bf     [local para salvar as ifnromacoes final de cada banco]
 * @param salvar [informacao de um banco para salvar]
 */
void salva_final(banco_final *bf, banco *salvar);
/**
 * [transferencia_bancos quando tem uma transferencia de um banco para o outro ]
 * @param operacao [banco que vai enviar]
 * @param recebe   [banco que vai receber]
 */
void transferencia_bancos(itens *operacao, banco *recebe);

void ordena_final(banco_final *bf);

/**
 * [imprime_auditoria pega as informacoes e ve se tem auditoria e imprime a quantidade de dados pedido pelo usuario]
 * @param total      [quantiade total de itens entrada na entrada]
 * @param apartir_de [onde comeca os dados da auditoria]
 * @param entradas   [onde estao as informacoes pedidas para a auditoria]
 * @param terminais  [para acessa as informacoes do terminal, pega os valores pedidos]
 */
void imprime_auditoria(int apartir_de, int total, itens **entradas, terminal **terminais);

/**
 * [imprime_op_terminal imprime formatado que tipo de operacao esta fazendo auditoria]
 * @param c [qual operacao esta fazendo auditoria]
 * @param i [qual terminal esta fazendo auditoria]
 */
void imprime_op_terminal(char *c, int i);

/**
 * [imprime_item imprimi as informacoes para auditoria, os valores transitados]
 * @param i [onde as informacoes esta para imprimir]
 */
void imprime_item(itens *i);

/**
 * [libera_entrada libera a memoria das strings de entrada]
 * @param qnt   [quantidade de string]
 * @param dados [onde as strings estão armazenada]
 */
void libera_entrada(int qnt, char **dados);
/**
 * [libera_itens libera a memoria  das operacao feitas nos terminais]
 * @param qnt  [quantidade de operacao]
 * @param item [onde as operacoes estao salvas]
 */
void libera_itens(int qnt, itens **item);

/**
 * [libera_final description]
 * @param f [description]
 */
void libera_final(banco_final *f);

/**
 * [libera_terminal libera a memoria das informacoes salvas em cada terminal]
 * @param t [onde as informacoes do terminal esta salva]
 */
void libera_terminal(terminal **t);

/**
 * [salva_erro_final salva a quantidade de erro final]
 * @param e_f [erro total]
 * @param t   [erro vindo do terminal x]
 */
void salva_erro_final(erros *e_f, erros *t);

/**
 * [printa_erro rcebe um ponteiro para um estrutura de erro e imprime o resultado final]
 * @param e [erros para imprir]
 */
void printa_erro(erros *e);

#endif
