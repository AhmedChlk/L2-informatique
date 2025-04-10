#include <stdio.h>
#include <stdlib.h>
#include <myutils.h>

int* allouer_tab(int n){
    int* tab;
    tab = (int*) malloc (n*sizeof(int));
    for(int i=0;i<n;i++){
        tab[i] = 0;
    }
    printf("allocation faite avec succes\n");
    return tab;
}
void afficher_tab(int* tab, int n){
    for(int i=0;i<n;i++){
        printf("%d\n",tab[i]);
    }
}
int main(){
    int n;
    int* tab;
    lire_entier(&n,"entrez la taille de votre tableau : ","erreur veuillez entrer une taille valide");
    tab = allouer_tab(n);
    afficher_tab(tab,n);
    free(tab);
    return 0;
}