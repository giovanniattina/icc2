#include "linked_list.h"


void create_list(t_list *l){
	/*
		Funcion recibe a null list an create a t_item to be linked to the t_list
		In:
			l -> the new list
	*/
	//create a t_item to be linked to the t_list
	t_item *L = malloc(sizeof(t_item));

	l->qnt = 0;
	l->L = L;
	l->L->prev = l->L;//prev point to the t_list created
	l->L->next = l->L->prev;//next point to prev of t_list 
}

void add_item(t_list *l, int item){
	/*
		Function create a t_item for save the new item and add to the top of the list
	*/
	//create a t_item for save the new item 

	t_item *t = malloc(sizeof(t_item));
	t->data.d = item;
	
	if(l->qnt == 0){//and is the fist item add make the sentinel last in it
		l->L->last = t;
	}

	t->next = l->L->next;//the t_item next point to the last item added in the list
	l->L->next->prev = t;//the last item add in the list point to the new item(using the prev node)
	l->L->next = t;//the t_list point to the new item 
	t->prev =  l->L;//the new item point to the t_list
	l->qnt++;

	l->L->first = t;//all the elements add is add at fisr item
}
void delete_item(t_list *l, t_item *item){
	/*
		Function recive a list and the pointer of the item to be remove
		In:
			l -> list to remove the item 
			item -> item to be remove
	*/

	l->qnt--;
	item->prev->next = item->next;// the item in the prev of the item to be remove point to the item that the item to be remove point in the next
	item->next->prev = item->prev;//the item in the next of the item to be remove point to the item in the prev
}

t_item *search(t_list *l, int item){
	/*
		Function recive a list and a value to be find in the list
		In:
			l-> list to search the item
			item -> value to be found in the list
		Out:
			t-> the item found or null if the item isn't in the list
	*/
	t_item *t = l->L->next;//go to the first item in the list
	while(t != l->L && t->data.d != item) t = t->next;//while won't came back to the first of the list and didn't find the item go to the next

	if(t == l->L) return NULL;

	return t;

}

void show_itens(t_list *l){
	/*
		Function recive a list and display all the item save
		In:
			l-> list to be displayed
	*/
	t_item *t = l->L->next;
	while(t != l->L){//while didn't go to the start of the list
		printf("%d\n", t->data.d);
		t = t->next;
	}
}

void add_sort(t_list *l, int item){
	/*
		Function recive a value to be add and a the list to add the value and add the value in ascending order
	*/
	t_item *t = malloc(sizeof(t_item));

	t->data.d = item;

	t_item *aux = l->L->next;

	if(l->qnt == 0){//if 0 both are the same item
		l->L->first = t;
		l->L->last = t;
	}else if(l->L->first->data.d > item){//if the pointer that is in first is bigger that the item change
		l->L->first = t;
	}else if(item > l->L->last->data.d){//if the pointer that is in first is smaller that the item change
		l->L->last = t;
	}

	while(aux != l->L && aux->data.d >= item) aux = aux->next;//find the first item that has a value higher value to the item to be  add

	aux->prev->next = t;//the prev item to the item found points to the new item
	t->prev = aux->prev; //the prev pointer of the new item points to the prev item
	t->next = aux; //the new item points to the item found in next pointer
	aux->prev = t;// the prev pointeir in the item founded points to the new item 
	l->qnt--;

}
