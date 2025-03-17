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
    int tab[8] = {1, 4,3, 1,2,7,10,11};
    int n = 8;
    for (int i = n / 2; i >= 0; i--) {
        descendre_tas(tab,n,i);
    }
    for (int i = 0; i <n; i++) {
        printf("%d ",tab[i]);
    }
    printf("\n");
    Tri_par_Tas(tab,n);
    printf("apres le Tri : \n");
    for (int i = 0; i <n; i++) {
        printf("%d ",tab[i]);
    }
    printf("\n");

}   