#include <stdio.h>
#include <stdlib.h>

typedef enum {
    A,
    B,
    C
} indice_socle_t;

typedef struct {
    indice_socle_t indice;
    int* diametres_disques;
    int nbr_disques_courant;
    int nbr_max_disques;
} socle_t;

// Fonction pour créer un socle
socle_t cree_socle(indice_socle_t indice, int nbr_max_disques) {
    socle_t s;
    s.indice = indice;
    s.nbr_max_disques = nbr_max_disques;
    s.nbr_disques_courant = 0;
    s.diametres_disques = (int*)malloc(nbr_max_disques * sizeof(int));
    return s;
}

// Fonction pour détruire un socle
void detruire_socle(socle_t* s) {
    if (s->diametres_disques != NULL) {
        free(s->diametres_disques);
        s->diametres_disques = NULL;
    }
    s->nbr_disques_courant = 0;
    s->nbr_max_disques = 0;
}

// Fonction pour afficher un socle
void afficher_socle(socle_t s) {
    printf("----- Affichage du socle -----\n");
    printf("Indice du socle : ");
    switch (s.indice) {
        case A: printf("A\n"); break;
        case B: printf("B\n"); break;
        case C: printf("C\n"); break;
    }
    printf("Nombre de disques actuels : %d\n", s.nbr_disques_courant);
    printf("Diamètres des disques (du bas vers le haut) :\n");
    for (int i = 0; i < s.nbr_disques_courant; i++) {
        printf("Disque %d : %d\n", i + 1, s.diametres_disques[i]);
    }
    printf("------------------------------\n");
}

// Programme principal
int main() {
    int n; // Nombre de disques
    printf("Entrez le nombre de disques : ");
    scanf("%d", &n);

    // Création des socles
    socle_t socleA = cree_socle(A, n);
    socle_t socleB = cree_socle(B, n);
    socle_t socleC = cree_socle(C, n);

    // Initialisation des disques sur le socle A
    for (int i = 0; i < n; i++) {
        socleA.diametres_disques[i] = n - i; // Plus grand disque en bas
    }
    socleA.nbr_disques_courant = n;

    // Affichage des socles
    afficher_socle(socleA);
    afficher_socle(socleB);
    afficher_socle(socleC);

    // Destruction des socles
    detruire_socle(&socleA);
    detruire_socle(&socleB);
    detruire_socle(&socleC);

    return 0;
}
