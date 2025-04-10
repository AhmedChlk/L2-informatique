#include <stdio.h>


char passage_ASCII(unsigned short car) {
    return (char)car;
}

int entier_car(char c) {
    return (int)c; 
}

int main() {
    // Afficher les 128 caractères de la table ASCII
    for(unsigned short i = 0; i <131072 ; i++) {
        printf("La valeur %d représente et le unsigned short de i est : %hu '%c'\n", i,(unsigned short)i, passage_ASCII(i));
    }


    return 0;
}
