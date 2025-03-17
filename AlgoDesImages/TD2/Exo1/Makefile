
CC      = gcc
CFLAGS  = -Wall -g -I../Exo1
SRC     = main.c interpolation.c ../../TD1/Exo2/ppm.c
OBJS    = main.o interpolation.o ppm.o
BIN     = main.exe

.PHONY: all clean run

all: $(BIN)

$(BIN): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) o $(BIN) -lm

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

ppm.o: ../../TD1/Exo2/ppm.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(BIN) $(OBJS) *.txt

run: $(BIN)
	./$(BIN)
