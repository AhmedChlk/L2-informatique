# Makefile principal pour AlgoDesImages

CC = gcc
CFLAGS = -Wall -Wextra  -Iinclude
LDFLAGS = -lm

# Définition des fichiers sources (chemins complets)
SRC_PGM    = src/td1/pgm/pgm.c
SRC_PPM    = src/td1/ppm/ppm.c
SRC_JPEG   = src/td1/jpeg/jpeg.c
SRC_TRANSF = src/td2/transfomation_dimages/transformations.c

SRC_FILES = $(SRC_PGM) $(SRC_PPM) $(SRC_JPEG) $(SRC_TRANSF)
OBJ_FILES = $(SRC_FILES:.c=.o)

# Définition des fichiers de test
TEST_FILES = tests/test_pgm.c tests/test_ppm.c tests/test_jpeg.c tests/test_transformations.c
TEST_OBJS = $(TEST_FILES:.c=.o)
TEST_PROGS = test_pgm test_ppm test_jpeg test_transformations

# Cible par défaut : compiler modules et programmes de test
all: $(OBJ_FILES) $(TEST_PROGS)

# Règle générique de compilation : pour tout fichier .c, générer l'objet correspondant
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Règles de liaison pour chacun des programmes de test
test_pgm: $(OBJ_FILES) tests/test_pgm.o
	$(CC) $(OBJ_FILES) tests/test_pgm.o -o test_pgm $(LDFLAGS)

test_ppm: $(OBJ_FILES) tests/test_ppm.o
	$(CC) $(OBJ_FILES) tests/test_ppm.o -o test_ppm $(LDFLAGS)

test_jpeg: $(OBJ_FILES) tests/test_jpeg.o
	$(CC) $(OBJ_FILES) tests/test_jpeg.o -o test_jpeg $(LDFLAGS)

test_transformations: $(OBJ_FILES) tests/test_transformations.o
	$(CC) $(OBJ_FILES) tests/test_transformations.o -o test_transformations $(LDFLAGS)

# Cible permettant d'exécuter tous les tests
test: $(TEST_PROGS)
	@echo "\n[Exécution des tests]" 
	./test_pgm
	./test_ppm
	./test_jpeg
	./test_transformations

# Cible de nettoyage
clean:
	rm -f $(OBJ_FILES) $(TEST_OBJS) $(TEST_PROGS)
	rm -f *.pgm *.ppm *.txt
