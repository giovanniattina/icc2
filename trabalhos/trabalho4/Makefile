all:
	gcc *.c estrutura_dados/*.c -Wall -g
run:
	./a.out

zip: 
	rm *.zip
	zip *.c *.h Makefile info.txt /estrutura_dados

val:
	valgrind --track-origins=yes  -v --leak-check=full ./a.out	