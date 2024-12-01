#include <stdio.h>
#include <stdlib.h>
#include <myutils.h>

void allouer_tab(int** tab ,int n){
    *tab = (int*) malloc (n*sizeof(int));
    for(int i=0;i<n;i++){
        (*tab)[i] = i+1;
    }
    
}

void modifier_taille_tab (int** t ,int n,int nouvelle_taille){
    int* new_tab;
    allouer_tab(&new_tab,nouvelle_taille);
    for(int i=0;i<n;i++){
        new_tab[i] = (*t)[i];
    }
    for(int i=n;i<nouvelle_taille;i++){
        new_tab[i] = 0;
    }
    free(*t);
    *t = new_tab;
}
void afficher_tab(int* tab, int n){
    for(int i=0;i<n;i++){
        printf("%d\n",tab[i]);
    }
}
int main(){
    int n;
    int* tab= NULL ;
    lire_entier(&n,"entrez la taille de votre tableau : ","erreur veuillez entrer une taille valide");
    allouer_tab(&tab,n);
    afficher_tab(tab,n);

    modifier_taille_tab(&tab,n,n+10);
    afficher_tab(tab,n+10);
    free(tab);
    return 0;
}