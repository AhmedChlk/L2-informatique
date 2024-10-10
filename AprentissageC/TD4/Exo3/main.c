#include <stdio.h>


char passage_ASCII(unsigned short car) {
    return (char)car;
}

int entier_car(char c) {
    return (int)c; 
}

int main() {
    // Afficher les 128 caractères de la table ASCII
    for(int i = 0; i < 128; i++) {
        printf("La valeur %d représente '%c'\n", i, passage_ASCII(i));
    }
    char example_char = 'A';
    printf("Le caractère '%c' correspond à l'entier %d\n", example_char, entier_car(example_char));

    return 0;
}
