#include "funcoes.h"



itens **separa_itens(char **entradas, int quantidade){

  int  lendo, r, bytes, item;
  float lido;
  char *op = (char*)malloc(sizeof(char));
  itens **dados = (itens**)malloc(sizeof(itens*)*quantidade);
  printf("%d\n", quantidade);
  for (int i = 0; i < quantidade; i++){
    printf("erro %d\n",i );
    dados[i] = (itens*)malloc(sizeof(itens)*1);
    lendo = 0; item =0;

    while ((r = sscanf(&(entradas[i][lendo]), "%f %n", &lido, &bytes)) != EOF) {

      if(r == 1){//se acho um numero
        printf("item lido %f\n", lido);
        switch (item) {
          case 0:
            (dados[i])->item1 = lido;
            break;

          case 1:
            dados[i]->item2 = lido;
            break;

          case 2:
            dados[i]->item3 = lido;
            break;

          case 3:
            dados[i]->item4 = lido;
            break;
        }
        item++;
        lendo += bytes;
      }else if(r == 0){
        r = sscanf(&(entradas[i][lendo]), "%s %n",op, &bytes);
        printf("op lida %s\n", op);
        if(r == 1){//acho um char
          dados[i]->o = strdup(op);
          lendo +=bytes;
        }
      }
    }
  }





  return dados;
}


terminal **processa_entrada(itens **entradas, int qnt){

  //aloca espaço para salvar os dados no terminal
  terminal **t;
  t = (terminal**)malloc(sizeof(terminal*)*4);
  for(int i = 0; i<4; i++){
    t[i] = (terminal*)malloc(sizeof(terminal));
  }

  for(int i = 0; i < qnt; i++){
    switch ((int)entradas[i]->item1) {//verifica o item 1 -- sempre é o terminal usado
      case 1:
      break;

      case 2:
      break;

      case 3:
      break;

      case 4:
      break;
    }
  }


  return t;
}
