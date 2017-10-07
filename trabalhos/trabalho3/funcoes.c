#include "funcoes.h"
#include "pilha.h"


void inicializa_dados(dados *d){
	/*
		Recebe um endereco da estrutura de dados e faz todos os valores 0
	*/
	d->object = 0;
	d->array = 0;
	d->pairs = 0; 
	d->strings = 0;
	d->numbers = 0;
	d->trues = 0;
	d->falses = 0; 
	d->nulls = 0;
}

int analizador_lexico(char *exp, dados *d){
	/*
		Funcao recebe a line de stream de dada pela entrada e faz a analize lexica, e faz analize sintatica quando
		acha , : } ] em especificas condições
		Saida:
			0 -> sem erro
			1 -> erro na analize
	*/

	int tam = strlen(exp);
	int inicio, erro;
	int array = 0;
	int nao_e_string = 0;
	int objeto = 0;
	char aux;
	stack p;
	
	/*	
		tam -> tamanho do stream de dados;
		inicio -> para salvar aonde comecara a analize sintatica
		array -> para controla quando esta dentro de uma array
		nao_e_string -> para controla de tiver passando em um string e acha um char que pode encadiar uma analize sintica
		objeto -> para controlar quando esta dentro de uma array
		aux -> para salvar um chat qyuando precisar
	*/
	cria(&p);

	for(int i = 0; i< tam; i++){// verifica toda linha entrada

		if(exp[i] == '"'){// para controle se tiver  passando por uma string
			if(nao_e_string == 0)nao_e_string = 1;
			else nao_e_string = 0;	
			
		}
	
		if(exp[i] == '{'){//salva na pilha e inicio se achar começo de objeto
			push(&p, exp[i]);

			objeto = 1; array = 0;
			inicio = i+1; // salva novo inicio da analize sintatica
		}
		if(exp[i] == '}'){

			aux = pop(&p);

			if(aux == '{'){//se tiver em um objeto salva q acho objeto

				//analiza se tiver token
				erro = analiza_sintatico(exp, d, inicio, i-1);
				if(erro != 0){ //se retorna erro acaba analize
					return 1;
				}				
				d->object++;

			}else{//se nao tiver da erro lexico
				return 1;
			}
			d->pairs++;//contabiliza novo pair
			inicio = i+1; objeto = 0; 

			if(p.qnt > 0){//se tiver item na pilha ainda
				aux = pop(&p);
				if(aux == '{')	objeto = 1; // se tiver um { ainda esta dentro de um objeto
				push(&p, aux);
			}
		}

		if(exp[i] == '['){//se começa uma array acha salva na pilha

			push(&p, exp[i]);
			inicio = i+1;
			array = 1;

		}
		if(exp[i] == ']'){// para analizar se acho o final de uma array 

			array = 0;
			aux = pop(&p);
			if(aux == '['){//se acho o começa array conta uma array
				//analiza o dado
				erro = analiza_sintatico(exp, d, inicio, i-1);
				if(erro != 0){ //se retorna erro acaba analize
					return 1;
				}	
				d->array++;
			}else{//se nao acho retorna erro
				return 1;
			}

			inicio = i+1;
		}


		if(exp[i] == ':' && nao_e_string == 0){//se achar : faz a analize sintatica do nao terminal 
			erro = analiza_sintatico(exp, d, inicio, i-1);
			if(erro == 1){// se tiver retorna erro
				return 1;
			}
			inicio = i +1;
			if(array != 0) return 1; //se tiver um não termial dentro de uma array da erro, não pode termial
		}

		if(exp[i] == ','){//ve se tem um tokem para analizar
			//faz analize do token 
			erro = analiza_sintatico(exp, d, inicio, i-1);
			if(erro == 1){// se tiver retorna erro
					return 1;
			}
			if(array == 0 && objeto == 1) {// para conta pair, nao pode esta entro de um array e tem q estar em um objeto
				d->pairs++; //se nao estiver dentro de uma array conta como pair
			}
			inicio = i+1;
		}


		if(exp[i] == 92){//se achar um barra termina analiza e retorna erro

			if(exp[i+1] == 'b' || exp[i+1] == 'f' || exp[i+1] == 'n' || exp[i+1] == 'r' || exp[i+1] == 't'|| exp[i+1] == 'u' ){
				return 1;				
			}else{
				continue;
			}
		}
	}
	return 0;
}

int analiza_sintatico(char *exp, dados *d, int inicio, int fim){
	/*
		Faz a analise sintatica do token ou nao terminal, nesta funcao faz analise de string, chamando no 
		final para	numeros, true, false e null.
		Entrada:
			-exp: expressao q esta analizando
			-d: para salvar o que analizou
			-inicio: para pegar ponteiro de inicio da analize
			-saida: para pegar poonteiro final da analize
		Saida:
			0 - sem erros
			1 - Tem erro
	*/

	int comeco_string = 0;
	int erro;	
	char aux;
	stack p;
	/*
		comeco_string: variavel auxiliar para ajudda na contabilizacao de string
		erro: recebe retorno de outra funcao se tiver erro
		aux: se precisar salvar um char
	*/
	cria(&p);
	for(int i = inicio; i <= fim; i++){//analiza char por char

		if(exp[i] == '"'){//se acha um ", comeco de string
			if(comeco_string == 0){//se não tiver passado por nenhum a priori
				push(&p, exp[i]);
				comeco_string = 1;
			}else{//se não passou verifica se tem um " na pilha e se tiver contabiliza uma string
				
				//se for um stream de char igual a """ da erro, pois nao e' permitido
				if(exp[i+1] == '"'){
					return 1;
				}

				aux = pop(&p);// ve^ o que esta na pilha 
				if(aux == '"'){//se tiver " e' char
					d->strings++;
					comeco_string = 0;
				}else{
					push(&p, aux);
				}
			}
		}		
		
	}

	erro = analiza_token(d, exp, inicio, fim);//analize outros tipo de dado
	//se retorna 1, deu erro
	if(erro != 0){
		return 1;
	}
	erro = analizado_numero(d, exp, inicio, fim); //analiza numero
	if(erro != 0){
		return 1;
	}
	return 0;
}
int analizado_numero(dados *d, char *exp, int inicio, int fim){
	/*
		Faz a analise sintatica do token, fazendo a analize de numeros
		Entrada:
			-exp: expressao q esta analizando
			-d: para salvar o que analizou
			-inicio: para pegar ponteiro de inicio da analize
			-saida: para pegar poonteiro final da analize
		Saida:
			0 - sem erros
			1 - Tem erro
	*/
	int e_numero= 0; //para salvar se e numero

	for(int i = inicio; i<=fim; i++){//anda char por char
		if(exp[i] == '"' ){//se começar com " e uma string e termina a analize
			return 0;
		}else if((exp[i] == '[' || exp[i] == ' ' || exp[i] == ']')){//se for [, espaco ou , continua
			continue;
		}

		if(exp[i] == ',' && e_numero == 1){//se achar uma virgula e tiver contabilizado numero adiciona numero
			e_numero = 0;
			d->numbers++;
		}

		if((exp[i] >= 48 && exp[i] <= 57) || exp[i] == '.' || exp[i] == 'e' || exp[i] == 'E' || exp[i] == '+' || exp[i] == '-'){
			//se for um numero, um ponto, um exponencial ou um sinal pode ser um numero
			if((exp[i] == 'e' || exp[i] == 'E')){//se for e|E o proximo nao pode ser outro e|E apenas numero ou simbolo
				if(exp[i+1] == 'e' || exp[i+1] == 'E') return 1;
				if(exp[i+1] == ']' || exp[i+1] == ',' || exp[i+1] == '}') continue; //se achar um e sozinho nao contabiliza como exponecial porq ele tem q ter um um valor depois
			}

			e_numero = 1;

		}else if(e_numero == 1){//se achar algo que nao da um numero ou expressao numerica em um stream de numero, da erro
			return 1;
		}else{
			e_numero = 0;
			continue;
		}
	}
	if(e_numero == 1){//se acabar o stream e tinha um numero adicionar o numero
		d->numbers++;
	}

	return 0;
}
int analiza_token(dados *d, char *exp, int inicio, int fim){
	/*
		Faz a analise sintatica do token, fazendo a analize de true, false, null
		Entrada:
			-exp: expressao q esta analizando
			-d: para salvar o que analizou
			-inicio: para pegar ponteiro de inicio da analize
			-saida: para pegar poonteiro final da analize
		Saida:
			0 - sem erros
			1 - Tem erro
	*/
	char t[4] = {'t', 'r', 'u', 'e'};//para analizar true
	char f[5] = {'f', 'a', 'l', 's', 'e'};//para analizar false
	char n[4] = {'n', 'u', 'l', 'l'};//para analizar null
	int index_t = 0;//index para true
	int index_f = 0;//index para false
	int index_n = 0;//index para null

	for (int i = inicio; i <= fim; ++i){//analiza todos os cahr

		//se for começo de string para de analizar e volta para de analizar
		if(exp[i] == '"'){
			break;
		}

		//se for um sinal tem que ter um numero antes se nao tiver da erro
		if(exp[i] == 43 || exp[i] == 45){

			if(!((exp[i+1] >= 46 && exp[i+1] <= 57) || exp[i+1] == 'e')){
				//printf("erro\n");
				return 1;
			}
		}

		//se for qualquer coisa nao seja numero, e, ou true, false e null, da erro na analize
		if(!(exp[i] >= 48 && exp[i] <= 57) && (exp[i] == 'e' && exp[i] == 'f' && exp[i] == 'a' && exp[i] == 'l'&& exp[i] == 's' && exp[i] == 'e'&& exp[i] == 't'&& exp[i] == 'r'&& exp[i] == 'u'&& exp[i] == 'n'&& exp[i] == 'u'&& exp[i] == 'l')){
			return 1;
		}

		//analize de true
		if(exp[i] == t[index_t]){//se for true
			if(index_t == 3){//se chegou na ultima letra
				if(exp[i+1] == ',' ||   exp[i+1] == '}' || exp[i+1] == ']'){
					//se chegou no final checa se o proximo item e um virgula separando itens de uma array ou final do token ou final de array
					d->trues++;
					index_t = 0;
				}else return 1;
			}
			
			index_t++;
		}

		//analize de false
		if(exp[i] == f[index_f]){//se for false
			if(index_f == 4){//se chegou na ultima letra
				if(exp[i+1] == ',' ||   exp[i+1] == '}' || exp[i+1] == ']'){
					//se chegou no final checa se o proximo item e um virgula separando itens de uma array ou final do token ou final de array
					d->falses++;
					index_f = 0;
				}else return 1;					
			}
			index_f++;
		}

		//analize de false
		if(exp[i] == n[index_n]){//se for null
			if(index_n == 3){//se chegou na ultima letra
				if(exp[i+1] == ',' ||   exp[i+1] == '}' || exp[i+1] == ']' || exp[i+1] == ' '){
					//se chegou no final checa se o proximo item e um virgula separando itens de uma array ou final do token ou final de array
					d->nulls++;
					index_n = 0;
				}else return 1;					
			}
			index_n++;
		}
	}
	
	return 0;
}

void print_dados(dados *d){
	/*
		Funcao recebe os dados de entrada e imprime resultado
	*/
	fprintf ( stdout , "Number of Objects: %d\n" , d->object );
	fprintf ( stdout , "Number of Arrays: %d\n" , d->array );
	fprintf ( stdout , "Number of Pairs: %d\n" , d->pairs );
	fprintf ( stdout , "Number of Strings: %d\n" , d->strings );
	fprintf ( stdout , "Number of Numbers: %d\n" , d->numbers );
	fprintf ( stdout , "Number of Trues: %d\n" , d->trues );
	fprintf ( stdout , "Number of Falses: %d\n" , d->falses );
	fprintf ( stdout , "Number of Nulls: %d\n" , d->nulls);
}