#include <stdio.h>
#include <stdlib.h>
#include "arbre_utils.h"

int max(int a,int b){
    if(a<b)
        return b;
    else    
        return a;
}
noeud_t* create_node(int val){
    noeud_t* new = (noeud_t*) malloc(sizeof(noeud_t));
    new->val = val;
    new->fg = NULL;
    new->fd=NULL;
    return new;
}

int calculer_hauteur(arbre_t A){
    if(A == NULL){
        return -1; 
    }else{
        return 1 + max(calculer_hauteur(A->fg),calculer_hauteur(A->fd));
    }
}
int calculer_nombre_noeuds(arbre_t A){
    if (A == NULL){
        return 0;
    }else{
        return 1 + calculer_nombre_noeuds(A->fg) + calculer_nombre_noeuds(A->fd);
    }
}


void inserer_noeud_parfaitement_equilibre(arbre_t* A,int val){
    if(*A == NULL){
        noeud_t* new = create_node(val);
        *A = new;
    }else if(calculer_nombre_noeuds((*A)->fg) - calculer_nombre_noeuds((*A)->fd) == 1){
        inserer_noeud_parfaitement_equilibre(&((*A)->fd),val);
    }else{
        inserer_noeud_parfaitement_equilibre(&((*A)->fg),val);
    }
    
}

void inserer_arbre_binaire_de_recherche(arbre_t* A,int val){
    if(*A == NULL){
        noeud_t* new = create_node(val);
        *A = new;
    }else if(val > (*A)->val){
        inserer_arbre_binaire_de_recherche(&((*A)->fd),val);
    }else if (val < (*A)->val){
        inserer_arbre_binaire_de_recherche(&((*A)->fg),val);
    }

}

arbre_t* construire_arbre_binaire_de_recherche(int* tab_val,int n){
    arbre_t* A = (arbre_t*) malloc(sizeof(arbre_t));
    for(int i=0;i<n;i++){
        inserer_arbre_binaire_de_recherche(A,tab_val[i]);
    }
    return A;
}


arbre_t* construire_arbre_parfaitement_equilibre(int* tab_val,int n){
    arbre_t* A = (arbre_t*) malloc(sizeof(arbre_t));
    for(int i=0;i<n;i++){
        inserer_noeud_parfaitement_equilibre(A,tab_val[i]);
    }
    return A;
}

void parcour_prefixe(arbre_t A){
    if(A != NULL){
        printf("%d ",A->val);
        parcour_prefixe(A->fg);
        parcour_prefixe(A->fd);
    }
}

void parcour_infixe(arbre_t A){
    if(A != NULL){
        parcour_infixe(A->fg);
        printf("%d ",A->val);
        parcour_infixe(A->fd);
    }
}

void parcour_postfixe(arbre_t A){
    if(A != NULL){
        parcour_postfixe(A->fg);
        parcour_postfixe(A->fd);
        printf("%d ",A->val);
    }
}

void affichage_indentation_rec (arbre_t A , int i , int hauteur_racine){
    if(A!=NULL){
        for(int j=0;j<i;j++){
            printf("  ");
        }
        printf("%d\n",A->val);
        affichage_indentation_rec(A->fg,hauteur_racine - calculer_hauteur(A->fg),hauteur_racine);
        affichage_indentation_rec(A->fd,hauteur_racine - calculer_hauteur(A->fd),hauteur_racine);
    }
}

void affichage_indentation(arbre_t A){
    affichage_indentation_rec(A,0,calculer_hauteur(A));
}

arbre_t arbre_pe(int n){
    if (n==0) return NULL;
    int ng = n/2;
    int nd = n - ng -1;
    int x;
    printf("entrez une valeur svp : ");
    scanf("%d",&x);
    arbre_t t  = create_node(x);
    t->fg = arbre_pe(ng);
    t->fd = arbre_pe(nd);
    return t;
}

void print_node(noeud_t* n){
    printf("la valeur du noeud : %d\n"n->val);
    
}