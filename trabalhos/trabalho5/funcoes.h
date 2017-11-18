#ifndef FUNCOES_H
#define FUNCOES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SENTINELA -100.0

typedef struct{

  float item1, item2, item3, item4;
  char *o;
}itens;

typedef struct{
    int id;
    float saque, deposito, transferencia_entrou, transferencia_saiu;
}banco;

typedef struct{
    float lucro;
    itens **operacoes;
    int qnt_operacoes;
    banco **bancos;
    int qnt_bancos, *id_bancos;
}terminal;

typedef struct{
  banco *i_bancos;
  int qnt;
}banco_final;

typedef struct{
  int saque, transferencia, deposito, consulta, erro;
}erros;

/**
 * [separa_itens description]
 * @param  entradas   [description]
 * @param  quantidade [description]
 * @return            [description]
 */
itens **separa_itens(char **entradas, int quantidade, erros *e);

/**
 * [processa_entrada description]
 * @param  entradas [description]
 * @return          [description]
 */
terminal **processa_entrada(itens **entradas, int qnt, int *auditoria);

/**
 * [analiza_dado description]
 * @param  dado [description]
 * @return      [description]
 */
 int analiza_dado(itens *dado);

/**
 * [passa_para_terminal description]
 * @param operacao [description]
 * @param t        [description]
 */
void passa_para_terminal(itens *operacao, terminal *t);

/**
 * [processa_erro description]
 * @param c [description]
 * @param e [description]
 */
void processa_erro(char *c, erros *e);

/**
 * [hash description]
 * @param  terminal [description]
 * @param  banco    [description]
 * @return          [description]
 */
int hash(int terminal, int banco);

/**
 * [novo_espaco description]
 * @return [description]
 */
banco *novo_espaco();

/**
 * [salva_nova_operacao_banco description]
 * @param operacao [description]
 * @param b        [description]
 */
int salva_nova_operacao_banco(itens *operacao, banco *b);

/**
 * [relatorio description]
 * @param t [description]
 */
void relatorio(terminal **t, erros *e);
void mostra_info_banco(banco *b);
void salva_final(banco_final *bf, banco *salvar);
void transferencia_bancos(itens *operacao, banco *recebe);
void imprime_auditoria(int apartir_de, int total, itens **entradas, terminal **terminais);
void imprime_op_terminal(char *c, int i);
void imprime_item(itens *i);


void libera_entrada(int qnt, char **dados);
void libera_itens(int qnt, itens **item);
void libera_final(banco_final *f);
void libera_terminal(terminal **t);
#endif
