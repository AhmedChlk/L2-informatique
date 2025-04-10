#include <assert.h>
#include <stdio.h>
#include "arbre_utils.h"

int main(void) {
    printf("[Test] Début des tests unitaires de arbre_utils\n");

    /* Test 1 : Arbre vide */
    arbre_t A = NULL;
    assert(hauteur_arbre(A) == -1);
    assert(nombre_noeuds(A) == 0);
    assert(rechercher_arbre(A, 10) == NULL);
    
    /* Test 2 : Insertion */
    inserer_arbre_binaire_recherche(&A, 50);
    inserer_arbre_binaire_recherche(&A, 30);
    inserer_arbre_binaire_recherche(&A, 70);
    inserer_arbre_binaire_recherche(&A, 20);
    inserer_arbre_binaire_recherche(&A, 40);
    inserer_arbre_binaire_recherche(&A, 60);
    inserer_arbre_binaire_recherche(&A, 80);
    
    assert(nombre_noeuds(A) == 7);
    assert(hauteur_arbre(A) == 2);
    
    /* Test 3 : Recherche */
    noeud_t *n = rechercher_arbre(A, 70);
    assert(n != NULL && n->valeur == 70);
    n = rechercher_arbre(A, 99);
    assert(n == NULL);
    
    /* Test 4 : Parcours - Ici, nous affichons les résultats pour vérification visuelle */
    printf("Parcours préfixe récursif (attendu : 50 30 20 40 70 60 80) : ");
    parcours_prefixe(A);
    printf("\n");
    
    printf("Parcours infixe (attendu : 20 30 40 50 60 70 80) : ");
    parcours_infixe(A);
    printf("\n");
    
    printf("Parcours postfixe (attendu : 20 40 30 60 80 70 50) : ");
    parcours_postfixe(A);
    printf("\n");
    
    printf("Parcours préfixe itératif (attendu : 50 30 20 40 70 60 80) : ");
    parcours_prefixe_iteratif(A);
    
    /* Test 5 : Libération */
    detruire_arbre(&A);
    assert(A == NULL);
    
    printf("[Test] Tous les tests unitaires se sont déroulés avec succès.\n");
    return 0;
}
