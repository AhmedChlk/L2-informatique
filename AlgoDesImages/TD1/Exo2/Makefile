# Makefile pour Exo2

CC      = gcc
CFLAGS  = -Wall -g -I../Exo1
# Les fichiers sources : pour pgm.c, le chemin est relatif à Exo2.
SRC     = main.c ppm.c ../Exo1/pgm.c
OBJS    = main.o ppm.o pgm.o
BIN     = main.exe

.PHONY: all clean run

# La cible par défaut
all: $(BIN)

# Règle de création de l'exécutable à partir des objets
$(BIN): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(BIN)

# Règle générique pour compiler un fichier .c en .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Règle explicite pour pgm.o car le fichier source se trouve dans un autre dossier
pgm.o: ../Exo1/pgm.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(BIN) $(OBJS) *.pgm *.ppm *.txt

run: $(BIN)
	./$(BIN)
