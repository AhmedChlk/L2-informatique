#include <stdio.h>
#include <stdlib.h>
#include <arbre_utils.h>

arbre_t construire_arbre_equilibre(int* tab, int debut, int fin) {
    if (debut > fin) return NULL;
    int mid = (debut + fin) / 2;
    arbre_t racine = create_node(tab[mid]);
    racine->fg = construire_arbre_equilibre(tab, debut, mid - 1);
    racine->fd = construire_arbre_equilibre(tab, mid + 1, fin);
    return racine;
}


int main(){
    int tab_val[10] = {5,2,6,8,10,6,7,12,20,9};

}   