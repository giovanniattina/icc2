#ifndef FUNCOES_H
#define FUNCOES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{

  float item1, item2, item3, item4;
  char *o;
}itens;


typedef struct{
    float lucro;

}terminal;

/**
 * [separa_itens description]
 * @param  entradas   [description]
 * @param  quantidade [description]
 * @return            [description]
 */
itens **separa_itens(char **entradas, int quantidade);

terminal **processa_entrada(itens **entradas);

#endif
