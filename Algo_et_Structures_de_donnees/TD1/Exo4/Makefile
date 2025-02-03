CC = gcc
CFLAGS = -Wall -g -c

build : main.o arbre_utils.o
	$(CC) main.o arbre_utils.o -o main.exe

main.o :
	$(CC) $(CFLAGS) -I./.. main.c 

arbre_utils.o:
	$(CC) $(CFLAGS) ./../arbre_utils.c

clean : 
	rm -f *exe *.out *.o

run:
	./main.exe