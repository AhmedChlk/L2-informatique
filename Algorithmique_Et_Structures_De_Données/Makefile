# Makefile pour Algo_et_Structures_de_donnees

CC = gcc
CFLAGS = -Wall -Wextra -Iinclude

# Sources du programme principal
SRC = src/main.c src/arbre_utils.c
OBJ = $(SRC:.c=.o)

# Sources des tests
TEST_SRC = tests/test_arbre.c
TEST_OBJ = $(TEST_SRC:.c=.o)

# Cible par défaut : construit l'exécutable principal
all: main

main: $(OBJ)
	$(CC) $(CFLAGS) -o main $(OBJ)

# Cible "test" : construit l'exécutable de test
test: $(OBJ) $(TEST_OBJ)
	$(CC) $(CFLAGS) -o test $(OBJ) $(TEST_OBJ)

# Règle générique pour compiler les .c en .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Exécute les tests
run_tests: test
	./test

# Nettoyage
clean:
	rm -f src/*.o tests/*.o main test

.PHONY: all test run_tests clean
