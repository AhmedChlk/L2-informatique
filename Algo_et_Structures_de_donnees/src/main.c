#include <stdio.h>
#include <stdlib.h>
#include <arbre_utils.h>

int main(){
    int tab[7] = {10,20,30,40,50,60,70};
    arbre_t* A = construire_arbre_parfaitement_equilibre(tab,7);
    affichage_indentation (*A);
    
    return 0;






}