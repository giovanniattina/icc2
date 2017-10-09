//file to define the struct to save the dade and functions
#ifndef FUNCOES_H
#define FUNCOES_H

#include <stdio.h>
#include <stdlin.h>

/*
	Structure to save the data
	p0 -> indentification code
	t00 -> time to be recognize by the escalonator
	tf0 -> time to the process take to run
	r0 -> priorid*  of running 
*/
typedef struct{
	int p0, t00, tf0, r0;
}process;

typedef struct{
	process *p
}infos;

#endif