#ifndef PILHA_H
#define PILHA_H

#include <stdio.h>
#include <stdlib.h>


#define MAX 1001



typedef struct{
	char item;
}t_item;


typedef struct {
	int qnt;
	t_item itens[MAX];
}stack;


void cria(stack *p);
void push(stack *p, char item);
char pop(stack *p);
char remove_p(stack *p, int pos);
int empty(stack *p);
void print_stack(stack *p);
void clean_stack(stack *p);

#endif