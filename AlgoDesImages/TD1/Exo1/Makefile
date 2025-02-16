CC = gcc 
CFLAGS = -Wall -g
SRC = main.c pgm.c
exe : pgm.o main.o
	@$(CC) $(CFLAGS) $(SRC) -o main.exe

clean:
	@rm -f *.pgm *.txt *.exe *.o