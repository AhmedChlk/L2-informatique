#include <stdio.h>
#include <stdlib.h>
#include <myutils.h>

void allouer_tab(int** tab ,int n){
    *tab = (int*) malloc (n*sizeof(int));
    for(int i=0;i<n;i++){
        (*tab)[i] = 0;
    }
    
}
void afficher_tab(int* tab, int n){
    for(int i=0;i<n;i++){
        printf("%d\n",tab[i]);
        fflush(stdout);
    }
}
int main(){
    int n;
    int* tab= NULL ;
    lire_entier(&n,"entrez la taille de votre tableau : ","erreur veuillez entrer une taille valide");
    allouer_tab(&tab,n);
    afficher_tab(tab,n);
    free(tab);
    return 0;
}