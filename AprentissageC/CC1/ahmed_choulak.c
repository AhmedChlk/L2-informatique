#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 30
#define TAB_TAILLE 900
#define C 6

typedef struct{
    int couleur;
    int traitee;
}cellule;

typedef struct{
    cellule grille[N][N];
}grille;

typedef struct{
    int l;
    int c;
}position;

void remplir_grille (grille* tab){
    for(int i = 0 ; i<N;i++){
        for(int j=0;j<N;j++){
            tab->grille[i][j].couleur = rand() % C;
            tab->grille[i][j].traitee = 0;
        }
    }
}
void afficher_grille(grille tab){
        for(int i = 0 ; i<N;i++){
        for(int j=0;j<N;j++){
            printf("%d %d ",tab.grille[i][j].couleur,tab.grille[i][j].traitee);
        }
        printf("\n");
    }
}

void initialiser (position* T){
    for(int i=0;i<TAB_TAILLE;i++){
        T[i].l = -1;
        T[i].c = -1;
    }
}


void ajouter (position* T , position p){
    int i=0;
        while(T[i].l != -1 && T[i].c != -1 && (T[i].l != p.l && T[i].c != p.c) && i<TAB_TAILLE){
            i++;
        }
        if((T[i].l == p.l && T[i].c == p.c)){
            printf("la valeur existe deja dans le tableau\n");
        }
        else if (i<TAB_TAILLE){
            T[i] = p;
        }else{
            printf("erreur");
        }
    }
position retirer (position* T){
    int i;
    position p = T[0];
    for( i=0;i<TAB_TAILLE-1;i++){
        T[i] = T[i+1];
    }
    T[i+1].c = -1;
    T[i+1].l = -1;
    return p; 
 }
void afficher (position* T){
    int i = 0;
    while( i< TAB_TAILLE && T[i].l != -1 && T[i].c != -1){
        printf("%d %d \n",T[i].l,T[i].c);
        i++;
    }
}

void modifier_couleur(position* T, grille* G , int couleur) {
    position p = {0,0}; 
    int couleur_initialle = G->grille[0][0].couleur
    ajouter(T, p);
    
    while (T[0].l != -1 && T[0].c != -1) {
        p = retirer(T);
        
        G->grille[p.l][p.c].couleur = couleur;
        G->grille[p.l][p.c].traitee = 1;

        if (p.c + 1 < N && G->grille[p.l][p.c + 1].couleur == couleur_initialle) {
            ajouter(T, (position){p.l, p.c + 1});
        }
        
        if (p.c - 1 >= 0 && G->grille[p.l][p.c - 1].couleur == couleur_initialle) {
            ajouter(T, (position){p.l, p.c - 1});
        }
        
        if (p.l + 1 < N && G->grille[p.l + 1][p.c].couleur == couleur_initialle) {
            ajouter(T, (position){p.l + 1, p.c});
        }
        
        if (p.l - 1 >= 0 && G->grille[p.l - 1][p.c].couleur == couleur_initialle) {
            ajouter(T, (position){p.l - 1, p.c});
        }
    }
}

int main(){
    grille Floodit;
    position T[TAB_TAILLE],p = {1,2},f = {3,3};
    remplir_grille(&Floodit);
    // afficher_grille(Floodit);
    initialiser(T);
    afficher(T);
    ajouter(T,p);
    ajouter(T,f);
    afficher(T);
    position z;
    z = retirer(T);
    printf("apres 1er retirage : z= %d %d\n",z.l,z.c);

        for(int i=0;i<5;i++){
        printf("%d %d\n",T[i].l,T[i].c);
    }
    z = retirer(T);
    printf("apres 2eme retirage : z= %d %d\n",z.l,z.c);

        for(int i=0;i<5;i++){
        printf("%d %d\n",T[i].l,T[i].c);
    }


}