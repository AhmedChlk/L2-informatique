#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NOM_VILLE 100

// Définition des structures
typedef struct {
    int sommet;
    int valeur;
} couple_t;

typedef struct liste_couples_t {
    couple_t c;
    struct liste_couples_t* next;
} liste_couples_t;

typedef struct {
    liste_couples_t* liaisons_noeuds;
    char* nom_noeud;
} noeud_t;

typedef struct{
    int nbr_noeuds;
    noeud_t* tab_noeud;
} graphe_t;

// Fonctions de manipulation des listes de couples

void inserer_couple(liste_couples_t** L, int s, int d){
    liste_couples_t* nouveau = (liste_couples_t*) malloc(sizeof(liste_couples_t));
    if (nouveau == NULL) {
        fprintf(stderr, "Erreur d'allocation mémoire\n");
        exit(EXIT_FAILURE);
    }
    nouveau->c.sommet = s;
    nouveau->c.valeur = d;
    nouveau->next = NULL;

    if(*L == NULL){
        *L = nouveau;
    } else {
        liste_couples_t* temp = *L;
        while(temp->next != NULL){
            temp = temp->next;
        }
        temp->next = nouveau;
    }
}

couple_t extraire_couple_min_valeur(liste_couples_t** L){
    if (L == NULL || *L == NULL){
        // Liste vide, retourner un couple invalide
        return (couple_t){-1, -1};
    }

    liste_couples_t* courant = *L;
    liste_couples_t* precedent = NULL;

    liste_couples_t* min_node = courant;
    liste_couples_t* min_prev = NULL;
    int min_val = courant->c.valeur;

    while(courant != NULL){
        if(courant->c.valeur < min_val){
            min_val = courant->c.valeur;
            min_node = courant;
            min_prev = precedent;
        }
        precedent = courant;
        courant = courant->next;
    }

    // Supprimer min_node de la liste
    if(min_prev == NULL){
        // min_node est la tête de la liste
        *L = min_node->next;
    }
    else{
        min_prev->next = min_node->next;
    }

    couple_t c = min_node->c;
    free(min_node);
    return c;
}

void mettre_a_jour_couple(liste_couples_t** L, int s, int d){
    liste_couples_t* temp = *L;
    while(temp != NULL && temp->c.sommet != s){
        temp = temp->next;
    }
    if(temp != NULL && temp->c.sommet == s){
        temp->c.valeur = d;
    } else {
        inserer_couple(L, s, d);
    }
}

void afficher_couple(liste_couples_t* L){
    while(L != NULL){
        printf("(%d,%d) ", L->c.sommet, L->c.valeur);
        L = L->next;
    }
}

void detruire_couple(liste_couples_t** L){
    if(L != NULL){
        while(*L != NULL){
            liste_couples_t* temp = *L;
            *L = (*L)->next;
            free(temp);
        }
        *L = NULL;
    }
}

// Fonction de construction du graphe

graphe_t construire_graphe(const char* nom_fichier){
    graphe_t G;
    FILE* F = fopen(nom_fichier, "r");
    if(F == NULL){
        fprintf(stderr, "Erreur d'ouverture du fichier %s\n", nom_fichier);
        exit(EXIT_FAILURE);
    }
    
    if(fscanf(F, "%d", &G.nbr_noeuds) != 1){
        fprintf(stderr, "Erreur de lecture du nombre de noeuds\n");
        fclose(F);
        exit(EXIT_FAILURE);
    }

    G.tab_noeud = (noeud_t*) malloc(G.nbr_noeuds * sizeof(noeud_t));
    if(G.tab_noeud == NULL){
        fprintf(stderr, "Erreur d'allocation mémoire pour les noeuds\n");
        fclose(F);
        exit(EXIT_FAILURE);
    }

    for(int i = 0; i < G.nbr_noeuds; i++){ 
        G.tab_noeud[i].nom_noeud = (char*) malloc(MAX_NOM_VILLE * sizeof(char));
        if(G.tab_noeud[i].nom_noeud == NULL){
            fprintf(stderr, "Erreur d'allocation mémoire pour le nom du noeud %d\n", i);
            // Libération des précédentes allocations avant de quitter
            for(int j = 0; j < i; j++){
                free(G.tab_noeud[j].nom_noeud);
                detruire_couple(&G.tab_noeud[j].liaisons_noeuds);
            }
            free(G.tab_noeud);
            fclose(F);
            exit(EXIT_FAILURE);
        }
        if(fscanf(F, "%s", G.tab_noeud[i].nom_noeud) != 1){
            fprintf(stderr, "Erreur de lecture du nom du noeud %d\n", i);
            // Libération des allocations avant de quitter
            for(int j = 0; j <= i; j++){
                free(G.tab_noeud[j].nom_noeud);
                detruire_couple(&G.tab_noeud[j].liaisons_noeuds);
            }
            free(G.tab_noeud);
            fclose(F);
            exit(EXIT_FAILURE);
        }
        G.tab_noeud[i].liaisons_noeuds = NULL;
    }

    int s1, s2, d;
    while(fscanf(F, "%d:%d:%d", &s1, &s2, &d) == 3){
        if(s1 >= G.nbr_noeuds || s2 >= G.nbr_noeuds || s1 < 0 || s2 < 0){
            fprintf(stderr, "Indice de sommet invalide: %d ou %d\n", s1, s2);
            continue; // Ignorer cette ligne et continuer
        }
        inserer_couple(&G.tab_noeud[s1].liaisons_noeuds, s2, d);
        inserer_couple(&G.tab_noeud[s2].liaisons_noeuds, s1, d);
    }

    fclose(F);
    return G;
}

// Fonction pour trouver l'indice d'un sommet donné son nom

int trouver_sommet(graphe_t G, const char* nom_ville){
    for(int i = 0; i < G.nbr_noeuds; i++){
        if(strcmp(G.tab_noeud[i].nom_noeud, nom_ville) == 0){
            return i;
        }
    }
    return -1;
}

// Fonction pour afficher le graphe

void afficher_graphe(graphe_t G){
    for(int i = 0; i < G.nbr_noeuds; i++){
        printf("G[%d] : %s -> ", i, G.tab_noeud[i].nom_noeud);
        afficher_couple(G.tab_noeud[i].liaisons_noeuds);
        printf("\n");
    }
}

// Fonction pour détruire le graphe et libérer la mémoire

void detruire_graphe(graphe_t* G){
    for(int i = 0; i < G->nbr_noeuds; i++){
        detruire_couple(&G->tab_noeud[i].liaisons_noeuds);
        free(G->tab_noeud[i].nom_noeud);
    }
    free(G->tab_noeud);
    G->nbr_noeuds = 0;
    G->tab_noeud = NULL;
}

// Fonction principale pour tester

int main(){
    // Test des fonctions de liste
    liste_couples_t* L = NULL;
    inserer_couple(&L, 3, 2);
    inserer_couple(&L, 4, 5);
    inserer_couple(&L, 11, 9);
    printf("Liste initiale :\n");
    afficher_couple(L);
    printf("\n\n\n Partie mise à jour \n");
    mettre_a_jour_couple(&L, 4, 6);
    mettre_a_jour_couple(&L, 8, 3);
    printf("Après mise à jour :\n");
    afficher_couple(L);

    printf("\n Partie extraction \n");
    couple_t c = extraire_couple_min_valeur(&L);
    printf("Liste après extraction du min :\n");
    afficher_couple(L);
    printf("Le min couple extrait : %d %d\n", c.sommet, c.valeur);
    printf("\n\n\n");
    printf("Partie Destruction \n");
    detruire_couple(&L);
    if(L == NULL){
        printf("Liste de couples détruite \n");
    } else {
        printf("Erreur: La liste de couples n'a pas été détruite correctement\n");
    }

    // Test de la fonction construire_graphe
    printf("\nConstruction du graphe à partir du fichier 'graph.txt'\n");
    graphe_t G = construire_graphe("graph.txt");
    printf("Graphe construit avec %d noeuds.\n", G.nbr_noeuds);
    afficher_graphe(G);

    // Exemple d'utilisation de trouver_sommet
    char nom_ville_recherchee[MAX_NOM_VILLE];
    printf("\nEntrez le nom d'une ville à rechercher: ");
    scanf("%s", nom_ville_recherchee);
    int indice = trouver_sommet(G, nom_ville_recherchee);
    if(indice != -1){
        printf("La ville '%s' a l'indice %d dans le graphe.\n", nom_ville_recherchee, indice);
    }
    else{
        printf("La ville '%s' n'existe pas dans le graphe.\n", nom_ville_recherchee);
    }

    // Libération de la mémoire allouée pour le graphe
    detruire_graphe(&G);
    printf("Graphe détruit et mémoire libérée.\n");

    return 0;
}
