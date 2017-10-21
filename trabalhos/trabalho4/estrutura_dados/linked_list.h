#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdio.h>
#include <stdlib.h>
#include "../functions.h"


//struct to represent the data, can be change for any type of data
typedef struct {
	process *d;
}t_data;

//to represent and iten the list, with data save in it and pointers to points to the next and prev
typedef struct t_item t_item;

struct t_item{

	t_data data;
	t_item *next;
	t_item *prev;
    //sentinel for the first and last item
    t_item *first;
    t_item *last;

};
//the head of the list
typedef struct {
	int qnt;
	t_item *L;
}t_list;

typedef struct{
	int item1, item2, item3, item4;
	t_list p1, p2, p3, p4;
}prioridades;

//declarations of functions 
void create_list(t_list *l);
void add_item(t_list *l, process *item);
void delete_item(t_list *l, t_item *item);
process *retira_qualquer_item(t_list *t, int pos);
//t_item *search(t_list *l, int k);
//void show_itens(t_list *l);
void add_sort(t_list *l, process *item);
result *recebe_processos_f(infos *dados);
void adiciona_processos_lista(t_list *processos, infos *dados, int time);


#endif
