#include <stdio.h>

int main() {
    char chaine[255], caractere;
    int compteurCaractere = 0, i = 0;

    printf("Entrez votre chaine de caracteres : ");
    fgets(chaine, 255, stdin);


    printf("\nEntrez le caractere que vous voulez : ");
    caractere = getchar();


    while (chaine[i] != '\0') {
        if (chaine[i] == caractere) {
            compteurCaractere++;
        }
        i++;
    }

    printf("L'occurence du caractere est de : %d\n", compteurCaractere);

    return 0;
}
