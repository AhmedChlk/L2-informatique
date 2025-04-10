#include <stdio.h>
#include <stdlib.h>
#include <myutils.h>
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