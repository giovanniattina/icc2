#include "functions.h"

infos *recebe_dados(char *linha){
	int r, pos, num, c, controle;
	pos = 0; controle = 0;

	infos *dado = malloc(sizeof(infos));
	/*
		Controle -> Variavel para saber qual ponto salvar 	
	*/
	while ((r = sscanf(&linha[pos], "%d%n", &num, &c)) != EOF){//read all the line
	 // printf("%d %f %d\n", r, num, c);
		if (r == 1){//if is a digit
			printf("dado recebido%d\n", num);
			switch(controle){
				case 0:
				dado->p.p0 = num;
				case 1:
				dado->p.t00 = num;
				case 2:
				dado->p.tf0 = num;
				case 3:
				dado->p.r0 = num;
			}

			controle++;
	        pos += c;
	    }
	    if (r == 0) pos += c;//se achar um espaco
	        
	}

	return dado;
}