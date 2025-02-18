#ifndef ARBRE_UTILS
#define ARBRE_UTILS
    typedef struct noeud_t{
        int val;
        struct noeud_t *fg,*fd;
    }noeud_t;

    typedef noeud_t* arbre_t;

    noeud_t* create_node(int val);

    int calculer_hauteur(arbre_t A);

    int calculer_nombre_noeuds(arbre_t A);

    void inserer_noeud_parfaitement_equilibre(arbre_t* A,int val);

    void inserer_arbre_binaire_de_recherche(arbre_t* A,int val);

    arbre_t* construire_arbre_binaire_de_recherche(int* tab_val,int n);

    arbre_t* construire_arbre_parfaitement_equilibre(int* tab_val,int n);

    void parcour_prefixe(arbre_t A);

    void parcour_infixe(arbre_t A);

    void parcour_postfixe(arbre_t A);

    void  affichage_indentation_rec (arbre_t A , int i , int hauteur_racine);

    void affichage_indentation(arbre_t A);

    arbre_t arbre_pe(int n);

#endif