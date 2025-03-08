
CC      = gcc
CFLAGS  = -Wall -g -I../Exo1
SRC     = main.c jpeg.c ../Exo1/pgm.c
OBJS    = main.o jpeg.o pgm.o
BIN     = main.exe

.PHONY: all clean run

all: $(BIN)

$(BIN): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -lm -o $(BIN)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

pgm.o: ../Exo1/pgm.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(BIN) $(OBJS) *.txt

run: $(BIN)
	./$(BIN)
