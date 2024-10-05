#include <stdio.h>

int main() {
    char chaine[255], caractere;
    int  i = 0; //,trouve = 0 ,indiceOcc;

    printf("Entrez votre chaine de caracteres : ");
    fgets(chaine, 254, stdin);


    printf("\nEntrez le caractere que vous voulez : ");
    caractere = getchar();
/*
    while (chaine[i] != '\0' && trouve == 0) {
        if (chaine[i] == caractere) {
            trouve = 1;
            indiceOcc = i+1;
        }
        i++;
    }
*/
    while ( (chaine[i] != '\0') && /*trouve == 0*/ (chaine[i] != caractere)) {
        i++;
    }

    if (chaine[i] == '\0') 
        printf("aucune occurence n\'a ete trouve \n");
    else 
        printf("L'indince de la premiere occurence de \'%c\' est %d\n",caractere,i);

    return 0;
}
