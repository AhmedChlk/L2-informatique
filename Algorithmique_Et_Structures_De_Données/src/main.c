#include "arbre_utils.h"
#include <stdio.h>

int main(void) {
    arbre_t arbre = NULL;
    
    /* Insertion des valeurs dans l'arbre binaire de recherche */
    int valeurs[] = {50, 30, 70, 20, 40, 60, 80};
    int nb = sizeof(valeurs) / sizeof(valeurs[0]);
    for (int i = 0; i < nb; i++) {
        inserer_arbre_binaire_recherche(&arbre, valeurs[i]);
    }
    
    printf("Parcours préfixe (récursif) : ");
    parcours_prefixe(arbre);
    printf("\n");
    
    printf("Parcours préfixe (itératif) : ");
    parcours_prefixe_iteratif(arbre);
    
    printf("Parcours infixe : ");
    parcours_infixe(arbre);
    printf("\n");
    
    printf("Parcours postfixe : ");
    parcours_postfixe(arbre);
    printf("\n");
    
    printf("Nombre de noeuds : %d\n", nombre_noeuds(arbre));
    printf("Hauteur de l'arbre : %d\n", hauteur_arbre(arbre));
    
    /* Test de recherche */
    int val_rech = 60;
    noeud_t *n = rechercher_arbre(arbre, val_rech);
    if (n != NULL)
        printf("La valeur %d a été trouvée.\n", val_rech);
    else
        printf("La valeur %d n'a pas été trouvée.\n", val_rech);
    
    /* Libération de l'arbre */
    detruire_arbre(&arbre);
    
    return 0;
}
