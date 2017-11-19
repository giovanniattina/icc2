#include "funcoes.h"

//numeros primos utilizados para a funcao hash para salvar os itens de cada banco
const int tamanho_banco_terminal[MAX_TERMINAL] = {13,31,83,23};

itens **separa_itens(char **entradas, int quantidade, erros *e){

  int  lendo, r, bytes, item;
  float lido;

  char *op = (char*)malloc(sizeof(char)*10);
  itens **dados = (itens**)malloc(sizeof(itens*)*(quantidade+1));

  for (int i = 0; i < quantidade; i++){
    dados[i] = (itens*)calloc(1, sizeof(itens));
    lendo = 0; item =0;

    while ((r = sscanf(&(entradas[i][lendo]), "%f %n", &lido, &bytes)) != EOF) {

      if(r == 1){//se acho um numero
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
        r = sscanf(&(entradas[i][lendo]), "%s %n", op, &bytes);
        if(r == 1){//acho um char

          //se achar ERRO
          if(strcmp(op, "ERRO") == 0){
            //ve a entrada antiga e salva nos erros
            processa_erro(dados[i-1]->o, e);
            strcpy(dados[i-1]->o, "E");//troca o simbolado da ultima operacao para erro, para nao ser analizada
            break;
          }

          if(item == 1){
            dados[i]->item3 = SENTINELA;
            dados[i]->item4 = SENTINELA;
          }

          dados[i]->o = strdup(op);
          lendo +=bytes;
        }
      }
    }
  }
  free(op);
  return dados;
}


terminal **processa_entrada(itens **entradas, int qnt, int *auditoria){
  //aloca espaço para salvar os dados no terminal
  terminal **t;

  t = (terminal**)malloc(sizeof(terminal*)*MAX_TERMINAL);

  for(int i = 0; i<MAX_TERMINAL; i++){

    t[i] = (terminal*)calloc(1, sizeof(terminal));
    t[i]->operacoes = (itens**)calloc(10, sizeof(itens*));
    t[i]->bancos = (banco**)(banco**)calloc(tamanho_banco_terminal[i], sizeof(banco*));
  }

  for(int i = 0; i < qnt; i++){//analisza cada operacao entrada

    if(entradas[i]->item3 == SENTINELA){

      *auditoria = i;
      break;
    }
    switch ((int)entradas[i]->item1) {//verifica o item 1 -- sempre é o terminal usado
      case 1:
        passa_para_terminal(entradas[i], t[0]);
        break;

      case 2:
        passa_para_terminal(entradas[i], t[1]);
        break;

      case 3:
        passa_para_terminal(entradas[i], t[2]);
        break;

      case 4:
        passa_para_terminal(entradas[i], t[3]);
        break;
    }
  }


  return t;
}

void processa_erro(char *c, erros *e){
  if(strcmp(c, "S") == 0){
    e->saque++;
  }else if(strcmp(c, "T") == 0){
    e->transferencia++;
  }else if(strcmp(c, "C") == 0){
    e->consulta++;
  }else if(strcmp(c, "D") == 0){
    e->deposito++;
  }

  e->erro++;
}

void passa_para_terminal(itens *operacao, terminal *t){
  t->operacoes[t->qnt_operacoes++] = operacao;

  //acesso ao banco via hash
  int valor_hash = hash((int)operacao->item1, (int)operacao->item2);

  if(t->bancos[valor_hash] == NULL){//se não ja tiverem acessado o banco
    t->bancos[valor_hash] = novo_espaco();
    t->bancos[valor_hash]->id = operacao->item2;
    //salva id dos bancos usados no terminal
    t->id_bancos = (int*)realloc(t->id_bancos, (t->qnt_bancos+1)*sizeof(int));
    t->id_bancos[t->qnt_bancos] = operacao->item2;

    t->qnt_bancos++;
  }

  int retorno;
  retorno = salva_nova_operacao_banco(operacao, t->bancos[valor_hash]);
  //em caso de transferencia entre dois bancos
  if(retorno == 1){

    //verifico se o banco que ja foi criando ja tem espaco no level_aleatorio
    if(t->bancos[hash((int)operacao->item1, (int)operacao->item3)] == NULL){
      t->bancos[valor_hash] = novo_espaco();
      t->bancos[valor_hash]->id = operacao->item2;
      //salva id dos bancos usados no terminal
      t->id_bancos = (int*)realloc(t->id_bancos, (t->qnt_bancos+1)*sizeof(int));
      t->id_bancos[t->qnt_bancos] = operacao->item3;

      t->qnt_bancos++;
    }
    transferencia_bancos(operacao , t->bancos[hash((int)operacao->item1, (int)operacao->item3)]);
  }


  t->lucro = t->lucro +3;
}



int salva_nova_operacao_banco(itens *operacao, banco *b){
  //vejo qual operação é

  if(strcmp(operacao->o, "S") == 0){//se for saque
    b->saque = b->saque +  operacao->item3;
  }else if(strcmp(operacao->o, "D") == 0){//se for deposito
    b->deposito = b->deposito + operacao->item3;
  }else if(strcmp(operacao->o, "T") == 0){//se for transferencia;
    if(operacao->item4 == 0){//transferencia entre mesmo banco
      b->transferencia_saiu = b->transferencia_saiu + operacao->item3;
    }else{// se a transferencia for de bancos diferente demos que aumentar o saldo do outro banco
      b->transferencia_saiu = b->transferencia_saiu + operacao->item4;
      return 1;
    }
    //obs operacoes entre o mesmo banco nao tem diferente de saldo do mesmo banco
  }
  return 0;
}


int hash(int terminal, int banco){
  return banco%tamanho_banco_terminal[terminal-1];
}

banco *novo_espaco(){
  banco *b;
  b = (banco*)calloc(1, sizeof(banco));

  return b;
}

void ordena(int *valores, int qnt){
  int aux;
  for(int i = 0; i < qnt-1; i++){
    for(int j = i; j < qnt; j++){
      if(valores[i] > valores[j]){
        aux = valores[i];
        valores[i] = valores[j];
        valores[j] = aux;
      }
    }
  }
}

void relatorio(terminal **t, erros *e){
  float total_lucro = 0;
  int hash_valor;
  //para fazer o relatorio final
  banco_final *final;

  final = (banco_final*)calloc(1 ,sizeof(banco_final));
  final->i_bancos = (banco*)malloc(15*sizeof(banco));

  for (int i = 0; i < MAX_TERMINAL; i++) {
    printf("===TERMINAL %d===\n", i+1);
    //passo por cada banco do terminal i
    ordena(t[i]->id_bancos, t[i]->qnt_bancos);
    for(int j = 0; j < t[i]->qnt_bancos; j++){
      printf("Banco %d ", t[i]->id_bancos[j]);
      hash_valor = hash((int)i+1, t[i]->id_bancos[j]);
      mostra_info_banco(t[i]->bancos[hash_valor]);
      salva_final(final, t[i]->bancos[hash_valor]);
    }
    //salva infos para informacoes finais

    //imprime lucro de cada terminal i
    total_lucro += t[i]->lucro;
    printf("Lucro obtido %.2f\n",  t[i]->lucro);
  }
  //imprime final
  printf("===TOTAL===\n");
  ordena_final(final);
  for (int i = 0; i < final->qnt; i++) {
    printf("Banco %d Moeda +%.2f -%.2f Transferencia +%.2f -%.2f\n",  final->i_bancos[i].id ,final->i_bancos[i].deposito, final->i_bancos[i].saque, final->i_bancos[i].transferencia_entrou, final->i_bancos[i].transferencia_saiu );

  }
  printf("Lucro obtido %.2f\n", total_lucro);

  libera_final(final);

  //imprime erros
  if(e->saque > 0){
    printf("Erros saque: %d\n", e->saque);
  }
  if(e->deposito > 0){
    printf("Total de deposito %d\n", e->deposito);
  }
  if(e->consulta > 0){
    printf("Total de consulta %d\n", e->consulta);
  }
  if(e->transferencia > 0){
    printf("Erros transferencia %d\n", e->transferencia);
  }
  if(e->erro > 0){
    printf("Total de erros %d\n", e->erro);
  }
}

void mostra_info_banco(banco *final){
  printf("Moeda +%.2f -%.2f Transferencia +%.2f -%.2f\n",   final->deposito, final->saque, final->transferencia_entrou, final->transferencia_saiu );
}

void salva_final(banco_final *bf, banco *salvar){
  //ve se já tem salvo
  for(int i =0 ; i < bf->qnt; i++){
    if(bf->i_bancos[i].id == salvar->id){
      bf->i_bancos[i].saque += salvar->saque;
      bf->i_bancos[i].deposito += salvar->deposito;
      bf->i_bancos[i].transferencia_saiu += salvar->transferencia_saiu;
      bf->i_bancos[i].transferencia_entrou += salvar->transferencia_entrou;
      return;
    }
  }
  bf->i_bancos[bf->qnt].id = salvar->id;
  bf->i_bancos[bf->qnt].saque += salvar->saque;
  bf->i_bancos[bf->qnt].deposito += salvar->deposito;
  bf->i_bancos[bf->qnt].transferencia_saiu += salvar->transferencia_saiu;
  bf->i_bancos[bf->qnt].transferencia_entrou += salvar->transferencia_entrou;
  bf->qnt++;

}
void ordena_final(banco_final *bf){
  banco aux;
  for(int i = 0; i < bf->qnt -1; i++){
    for(int j = i ; j < bf->qnt; j++){
      if(bf->i_bancos[i].id > bf->i_bancos[j].id){
        aux = bf->i_bancos[i];
        bf->i_bancos[i] = bf->i_bancos[j];
        bf->i_bancos[j] = aux;
      }
    }
  }
}

void transferencia_bancos(itens *operacao, banco *recebe){
  recebe->transferencia_entrou += operacao->item4;

}

void imprime_auditoria(int apartir_de, int total, itens **entradas, terminal **terminais){
  printf("===AUDITORIA===\n");
  int j, k;

  for(int i = apartir_de; i < total-1; i++){
    //vejo quantas vezes vou ter que repedi a operacao no valor q esta no item2
    imprime_op_terminal(entradas[i]->o, entradas[i]->item1);
    j = 0; k = 0;
    printf("Mostrando primeiros %d resultados\n", (int)entradas[i]->item2);
      while((j < (int)entradas[i]->item2) && (k < terminais[(int)entradas[i]->item1-1]->qnt_operacoes)){
      if(strcmp(terminais[(int)entradas[i]->item1-1]->operacoes[k]->o, entradas[i]->o) == 0 ){
        printf("%d-", j+1);
        imprime_item(terminais[(int)entradas[i]->item1-1]->operacoes[k]);
        j++;
      }
      k++;
    }
    if(j == 0){
      printf("Sem resultados\n");
    }
  }
}

void imprime_op_terminal(char *c, int i){
  if(strcmp(c, "S") == 0){
    printf("===SAQUE TERMINAL %d===\n", i);
  }else if(strcmp(c, "T") == 0){
    printf("===TRANSFERENCIA TERMINAL %d===\n", i);
  }else if(strcmp(c, "D") == 0){
    printf("===DEPOSITO TERMINAL %d===\n", i);
  }

}

void imprime_item(itens *i){
  if(strcmp(i->o, "S") == 0){
    printf("Banco %d %.2f\n", (int)i->item2, i->item3);
  }else if(strcmp(i->o, "T") == 0){
    if(i->item4 != 0){
      printf("Banco origem %d Banco destino %d %.2f\n", (int)i->item2, (int)i->item3, i->item4);

    }else{
      printf("Banco origem %d Banco destino %d %.2f\n", (int)i->item2, (int)i->item2, i->item3);

    }
  }else if(strcmp(i->o, "D") == 0){
    printf("Banco %d %.2f\n", (int)i->item2, i->item3);

  }

}

void libera_final(banco_final *f){
  free(f->i_bancos);
  free(f);
}

void libera_entrada(int qnt, char **dados){
  for(int i = 0; i < qnt; i++) {
    free(dados[i]);
  }
  free(dados);
}

void libera_itens(int qnt, itens **item){
  for(int i = 0; i < qnt; i++){
    free(item[i]->o);
    free(item[i]);
  }
  free(item);
}

void libera_terminal(terminal **t){
  for(int i =0; i < MAX_TERMINAL; i++){

    for(int j =0; j < tamanho_banco_terminal[i]; j++){
      free(t[i]->bancos[j]);
    }
    //free(t[i]->bancos);
    free(t[i]->id_bancos);
    free(t[i]->operacoes);
    free(t[i]);
  }
}
