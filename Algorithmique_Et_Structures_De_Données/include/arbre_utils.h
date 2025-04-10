#ifndef ARBRE_UTILS_H
#define ARBRE_UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* Définition d'un nœud d'arbre binaire.
 * Chaque nœud contient une valeur entière, et des pointeurs vers les sous-arbres gauche et droit.
 */
typedef struct noeud {
    int valeur;
    struct noeud *gauche;
    struct noeud *droite;
} noeud_t;

typedef noeud_t* arbre_t;

/* Création d'un nœud.
 * Alloue et initialise un nœud contenant la valeur donnée.
 * Retourne un pointeur sur le nœud créé.
 */
noeud_t* creer_noeud(int valeur);

/* Insertion dans un arbre binaire de recherche.
 * Insère la valeur dans l'arbre de façon à maintenir l'ordre (les valeurs inférieures à la racine vont à gauche, les supérieures à droite).
 */
void inserer_arbre_binaire_recherche(arbre_t *arbre, int valeur);

/* Recherche d'une valeur dans un arbre binaire de recherche.
 * Retourne un pointeur vers le nœud contenant la valeur, ou NULL si non trouvée.
 */
noeud_t* rechercher_arbre(arbre_t arbre, int valeur);

/* Calcul de la hauteur d'un arbre.
 * Pour un arbre vide, retourne -1. Sinon, retourne la profondeur maximale (nombre de niveaux - 1).
 */
int hauteur_arbre(arbre_t arbre);

/* Calcul du nombre de nœuds dans l'arbre. */
int nombre_noeuds(arbre_t arbre);

/* Parcours préfixe récursif (racine, gauche, droite).
 * Affiche les valeurs sur la sortie standard, séparées par un espace.
 */
void parcours_prefixe(arbre_t arbre);

/* Parcours préfixe itératif (non récursif) à l'aide d'une pile statique. */
void parcours_prefixe_iteratif(arbre_t arbre);

/* Parcours infixe (gauche, racine, droite) récursif. */
void parcours_infixe(arbre_t arbre);

/* Parcours postfixe (gauche, droite, racine) récursif. */
void parcours_postfixe(arbre_t arbre);

/* Libération de la mémoire de l'arbre.
 * Libère récursivement tous les nœuds et met le pointeur à NULL.
 */
void detruire_arbre(arbre_t *arbre);

#endif /* ARBRE_UTILS_H */
