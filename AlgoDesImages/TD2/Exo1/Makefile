# Définition des répertoires
TD1_EXO1 = ../../TD1/Exo1
TD1_EXO2 = ../../TD1/Exo2

# Compiler et options
CC      = gcc
CFLAGS  = -Wall -g -I$(TD1_EXO1) -I$(TD1_EXO2) -I./

# Déclaration des sources et des objets
SRC     = main.c interpolation.c $(TD1_EXO2)/ppm.c $(TD1_EXO1)/pgm.c
OBJS    = $(SRC:.c=.o)
BIN     = main.exe

# Recherche des sources dans ces répertoires
VPATH = $(TD1_EXO1):$(TD1_EXO2):.

.PHONY: all clean run

all: $(BIN)

$(BIN): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(BIN) -lm

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(BIN) *.txt

run: $(BIN)
	./$(BIN)
