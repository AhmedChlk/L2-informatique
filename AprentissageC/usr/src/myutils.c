#include <stdio.h>
#include<myutils.h>

void lire_entier(int* var, char* chaine, char* chaine_erreur) {
    printf("%s", chaine);
    while (scanf("%d", var) != 1) {
        printf("%s\n", chaine_erreur);
        while (getchar() != '\n');
        printf("%s", chaine);
    }
}
void lire_element_tab(int* element ,char* chaine , int indice , char* chaine_erreur){
        printf("%s %d : ", chaine,indice);
    while (scanf("%d", element) != 1) {
        printf("%s\n", chaine_erreur);
        while (getchar() != '\n');
        printf("%s %d : ", chaine,indice);

    }
} 