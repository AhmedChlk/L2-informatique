#include <stdio.h>
#include <stdlib.h>
#include <arbre_utils.h>

int main(){
    int tab_val[10] = {10,20,30,40,50,60,70,80,90,100};
    arbre_t* A = construire_arbre_binaire_de_recherche(tab_val,10);
    noeud_t* n = recherche_ABR (*A,50);
    print_node(n);
}   