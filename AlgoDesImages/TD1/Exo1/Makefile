CC = gcc 
CFLAGS = -Wall -g
SRC = main.c pgm.c
exe : pgm.o main.o
	@$(CC) $(CFLAGS) $(SRC) -o main.exe

clean:
	@rm -f main eye_s_asc_ext.pgm eye_s_asc_neg.pgm eye_s_asc_from_bin.pgm eye_s_bin.pgm *.txt *.exe *.o