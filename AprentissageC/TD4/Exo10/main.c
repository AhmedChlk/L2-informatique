#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void afficher_tab(float tab[],int n){
    for(int i=0;i<n;i++){
        printf("tab[%d] : %f\n",i+1,tab[i]);
    }
}

void init_tab(float tab[],int n){
    for(int i=0;i<n;i++){
        tab[i] = (float) (rand() % 100) / (rand() % 100);
    }
}

void tri_bulle(float* tab,int n){
    float temp;
    for(int i=0;i<n;i++){
        for(int j=i+1;j<n;j++){
            if (*(tab+j) > *(tab+i)){
                temp = *(tab+i);
                *(tab+i) = *(tab+j);
                *(tab+j) = temp;

            }
        }
    }
}

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
int main(){
    srand(time(NULL));
    int n = 0;
    lire_entier(&n,"entrez la taille du tableau : ","erreur entrez une taille de tableau valide");
    float* tab = (float *) malloc (n * sizeof(float));
    init_tab(tab,n);
    printf("tableau avant le tri : \n");
    afficher_tab(tab,n);
    printf("tableau apres le tri : \n");
    tri_bulle(tab,n);
    afficher_tab(tab,n);


}