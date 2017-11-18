all:
	gcc *.c -Wall
run:
	./a.out

val:
	gcc *.c -Wall -g
	valgrind -v --track-origins=yes  --leak-check=full --show-leak-kinds=all ./a.out 
