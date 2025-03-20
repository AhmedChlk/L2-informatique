#include <stdio.h>
#include <stdlib.h>
#include <arbre_utils.h>


#define ESPACE 5  // Définir l'espace entre les niveaux d'affichage

// Fonction récursive pour afficher un arbre binaire de manière visuelle
void afficher_arbre_visuel(arbre_t racine, int espace) {
    if (racine == NULL) 
        return;

    espace += ESPACE;  // Augmenter l'espacement à chaque niveau

    // Affichage du sous-arbre droit en premier (meilleure visualisation)
    afficher_arbre_visuel(racine->fd, espace);

    // Affichage du nœud actuel avec indentation
    printf("\n");
    for (int i = ESPACE; i < espace; i++)
        printf(" ");
    printf("%d\n", racine->val);

    // Affichage du sous-arbre gauche
    afficher_arbre_visuel(racine->fg, espace);
}

// Fonction d'affichage avec appel initial
void afficher_arbre(arbre_t racine) {
    afficher_arbre_visuel(racine, 0);
}
int main(){
    arbre_t racine = NULL;

    // Création d'un arbre binaire de recherche
    inserer_arbre_binaire_de_recherche(&racine, 50);
    inserer_arbre_binaire_de_recherche(&racine, 30);
    inserer_arbre_binaire_de_recherche(&racine, 70);
    inserer_arbre_binaire_de_recherche(&racine, 20);
    inserer_arbre_binaire_de_recherche(&racine, 40);
    inserer_arbre_binaire_de_recherche(&racine, 60);
    inserer_arbre_binaire_de_recherche(&racine, 80);
   
    printf("Affichage visuel de l'arbre :\n");
    afficher_arbre(racine);
    BFS_arbre_binaire(racine);
    printf("\n");

}

