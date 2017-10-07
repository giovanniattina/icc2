#include "pilha.h"


void cria(stack *p){
	/*
		Creat one stack if zero elements
	*/

	p->qnt = 0;
}

void push(stack *p, char item){
	/*
		Add a item in the final of the stack
		In:	
			p: stack to add the item
			item: char to the added
	*/

	if(p->qnt == MAX -1){
		printf("cheira\n");
		exit(0);
	}
	t_item add;
	add.item = item;
	p->itens[p->qnt++] = add;
}
	
char remove_p(stack *p, int pos){
	/*
		This function remove a item in the pos passed thourgh the values
		In:remove_p
			p: struct to be uses
			pos: pos to be remove
	*/
	char ret = p->itens[pos].item;
	for(int i =  pos; i < p->qnt - 1; i++){
		p->itens[i] = p->itens[i+1];
	}
	p->qnt--;
	return ret;
}

char pop(stack *p){
	/*	
		Return the last element to enter in the stack
		In:
			p: stack to return element
		Out:
			return a char
	*/


	if(p->qnt <= 0){//check if is no empety
		return 0;
	}
	char aux;
	aux = p->itens[p->qnt-1].item; //element to be returned
	p->qnt--;
	return aux;

}



int empty(stack *p){
	/*
		Recive a stack and check if is empyte
		in:
			p> stack to be check
		out:
			0: has a member
			1:	not has a member
	*/

	if(p->qnt == 0){
		return 1;
	}else{
		return 0;
	}
}



void clean_stack(stack *p){
	/*
		Recive the stack strcut and change the qnt to zero
		In: 
			p: stack to be clean
	*/
	p->qnt = 0;
}
