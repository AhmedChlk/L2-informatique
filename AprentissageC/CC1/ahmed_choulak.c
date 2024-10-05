#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 10
#define TAB_TAILLE 100
#define  C 6

#define RESET_ALL    "\x1b[0m"
#define NOIR        "\x1b[30m"
#define ROUGE          "\x1b[31m"
#define VERT        "\x1b[32m"
#define JAUNE       "\x1b[33m"
#define CYAN         "\x1b[36m"
#define BLANC        "\x1b[37m"



typedef struct{
    int couleur;
    int traitee;
}cellule_t;

typedef struct{
    cellule_t grille[N][N];
}grille_t;

typedef struct{
    int l;
    int c;
}position_t;

void remplir_grille (grille_t* tab){
    for(int i = 0 ; i<N;i++){
        for(int j=0;j<N;j++){
            tab->grille[i][j].couleur = rand() % C;
            tab->grille[i][j].traitee = 0;
        }
    }
}
void print_couleur(char* couleur){
    printf("%s",couleur);
    printf(" ■ ");
    printf("%s",RESET_ALL);

}
void afficher_grille(grille_t tab){
        for(int i = 0 ; i<N;i++){
        for(int j=0;j<N;j++){
            switch(tab.grille[i][j].couleur){
                case 0:
                    print_couleur(ROUGE);
                    break;
                case 1:
                    print_couleur(BLANC);
                    break;
                case 2:
                    print_couleur(JAUNE);
                    break;
                case 3:
                    print_couleur(CYAN);
                    break;
                case 4:
                    print_couleur(VERT);
                    break;
                case 5:
                    print_couleur(NOIR);
                    break;

            }
        }
        printf("\n");
    }
}

void initialiser (position_t* T){
    for(int i=0;i<TAB_TAILLE;i++){
        T[i].l = -1;
        T[i].c = -1;
    }
}
void ajouter (position_t* T , position_t p){
    int i=0;
    while (i < TAB_TAILLE && T[i].l != -1 && T[i].c != -1) {
        if (T[i].l == p.l && T[i].c == p.c) {
            printf("La valeur existe déjà dans le tableau\n");
            return;
        }
        i++;
    }
    if (i<TAB_TAILLE){
            T[i] = p;
    }else{
            printf("erreur tableau plein");
    }
    }
position_t retirer (position_t* T){
    int i;
    position_t p = T[0];
    for( i=0;i<TAB_TAILLE-1;i++){
        T[i] = T[i+1];
    }
    T[TAB_TAILLE - 1].c = -1;
    T[TAB_TAILLE - 1].l = -1;
    return p; 
}
void afficher (position_t* T){
    int i = 0;
    while( i< TAB_TAILLE && T[i].l != -1 && T[i].c != -1){
        printf("%d %d \n",T[i].l,T[i].c);
        i++;
    }
}
int taille_region_adjacente(grille_t G, position_t* T) {
    position_t p = {0, 0};
    int taille_region = 0;
    int couleur_initiale = G.grille[0][0].couleur;

    ajouter(T, p);

    
    G.grille[p.l][p.c].traitee = 1;

    while (T[0].l != -1 && T[0].c != -1) {
        p = retirer(T);  
        taille_region++;

        
        if (p.c + 1 < N && G.grille[p.l][p.c + 1].couleur == couleur_initiale && G.grille[p.l][p.c + 1].traitee == 0) {
            ajouter(T, (position_t){p.l, p.c + 1});
            G.grille[p.l][p.c + 1].traitee = 1;  
        }

        if (p.c - 1 >= 0 && G.grille[p.l][p.c - 1].couleur == couleur_initiale && G.grille[p.l][p.c - 1].traitee == 0) {
            ajouter(T, (position_t){p.l, p.c - 1});
            G.grille[p.l][p.c - 1].traitee = 1;  
        }

        if (p.l + 1 < N && G.grille[p.l + 1][p.c].couleur == couleur_initiale && G.grille[p.l + 1][p.c].traitee == 0) {
            ajouter(T, (position_t){p.l + 1, p.c});
            G.grille[p.l + 1][p.c].traitee = 1;  
        }

        if (p.l - 1 >= 0 && G.grille[p.l - 1][p.c].couleur == couleur_initiale && G.grille[p.l - 1][p.c].traitee == 0) {
            ajouter(T, (position_t){p.l - 1, p.c});
            G.grille[p.l - 1][p.c].traitee = 1;  
        }
    }
    return taille_region;
}

void modifier_couleur(position_t* T, grille_t* G , int couleur) {
    position_t p = {0,0}; 
    int couleur_initialle = G->grille[0][0].couleur;
    ajouter(T, p);
    
    while (T[0].l != -1 && T[0].c != -1) {
        p = retirer(T);
        
        G->grille[p.l][p.c].couleur = couleur;
        G->grille[p.l][p.c].traitee = 1;

        if (p.c + 1 < N && G->grille[p.l][p.c + 1].couleur == couleur_initialle && G->grille[p.l][p.c + 1].traitee == 0) {
            ajouter(T, (position_t){p.l, p.c + 1});
        }
        
        if (p.c - 1 >= 0 && G->grille[p.l][p.c - 1].couleur == couleur_initialle && G->grille[p.l][p.c - 1].traitee == 0)  {
            ajouter(T, (position_t){p.l, p.c - 1});
        }
        
        if (p.l + 1 < N && G->grille[p.l + 1][p.c].couleur == couleur_initialle && G->grille[p.l + 1 ][p.c].traitee == 0) {
            ajouter(T, (position_t){p.l + 1, p.c});
        }
        
        if (p.l - 1 >= 0 && G->grille[p.l - 1][p.c].couleur == couleur_initialle && G->grille[p.l - 1][p.c].traitee == 0) {
            ajouter(T, (position_t){p.l - 1, p.c});
        }
    }
}
void reset_traitement (grille_t*G){
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            G->grille[i][j].traitee = 0;
        }
    }
}

void jouer_floodit(grille_t* G,position_t* T,int nombre_coup){
    int nombre_coup_jouee = 0,couleur_choisie;
    while(nombre_coup_jouee < nombre_coup && taille_region_adjacente(*G,T)!= TAB_TAILLE){
        printf("taille region adjacente : %d\n",taille_region_adjacente(*G,T));
        printf("voici la grille et il vous reste %d : \n",nombre_coup-nombre_coup_jouee);
        afficher_grille(*G);
        printf("entrez la couleur que vous voulez(entre 0 et 5) : \n 0 pour %s ROUGE %s\n 1 pour %s BLANC %s \n 2 pour %s JAUNE %s\n 3 pour %s CYAN %s\n 4 pour %s VERT %s\n 5 pour %s NOIR %s\n",ROUGE,RESET_ALL,BLANC,RESET_ALL,JAUNE,RESET_ALL,CYAN,RESET_ALL,VERT,RESET_ALL,NOIR,RESET_ALL);
        while(scanf("%d",&couleur_choisie)!= 1 && couleur_choisie >= 0 && couleur_choisie <= 0){
            printf("erreur entrez une coouleur valide \n");
            printf("entrez la couleur que vous voulez(entre 0 et 5) : \n 0 pour %s ROUGE %s\n 1 pour %s BLANC %s \n 2 pour %s JAUNE %s\n 3 pour %s CYAN %s\n 4 pour %s VERT %s\n 5 pour %s NOIR %s\n",ROUGE,RESET_ALL,BLANC,RESET_ALL,JAUNE,RESET_ALL,CYAN,RESET_ALL,VERT,RESET_ALL,NOIR,RESET_ALL);


        }
        modifier_couleur(T,G,couleur_choisie);
        reset_traitement(G);
        nombre_coup_jouee++;

    }
    if(taille_region_adjacente(*G,T)== TAB_TAILLE){
        printf("congratulations vous avez gagné\n");
    }
    else{
        printf("vous avez perdue\n");
    }
}
int main(){
    srand(time(NULL));
    grille_t Floodit;
    position_t T[TAB_TAILLE];
    remplir_grille(&Floodit);
    initialiser(T);
    jouer_floodit(&Floodit,T,10);
    return 0;
}
