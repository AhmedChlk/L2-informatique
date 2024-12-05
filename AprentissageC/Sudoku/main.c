#include<stdio.h>
#include<stdlib.h>

#define NB_LIGNES 9
#define NB_COLLONNES 9 

typedef struct {
    int valeur;
    int modifiable;
}cellule_t;
typedef struct{
    cellule_t** grille;
    int nb_lignes,nb_collonnes;
}grille_t;

typedef struct {
    int x,y;
}coordonees_t;

typedef struct pile_coordonnees_t {
    coordonees_t coordonee;
    struct pile_coordonnees_t* prev;
}pile_coordonnees_t;

pile_coordonnees_t* creer_pile_coordonnees (void){
    return NULL;
}

void detruire_pile_coordonnees(pile_coordonnees_t** p){
    while((*p)->prev != NULL){
        free(*p);
        (*p) = (*p)->prev;
    }
    p = NULL;
}
void empiler_coordonnees(pile_coordonnees_t** p,coordonees_t c){
    pile_coordonnees_t* N = (pile_coordonnees_t*)malloc(sizeof(pile_coordonnees_t));
    N->coordonee = c;
    N->prev = (*p);
    *p = N ;
}
void depiler_coordonnees(pile_coordonnees_t** p , coordonees_t* c){
    if(p != NULL && *p != NULL){
        *c = (*p)->coordonee;
        pile_coordonnees_t* temp = (*p);
        *p = (*p)->prev;
        free(temp);
        temp = NULL;
    }
    else{
        *c = (coordonees_t){-1,-1};
    }
}

void afficher_pile_coordonnees(pile_coordonnees_t* p){
    while(p != NULL){
        printf("%d %d\n",p->coordonee.x,p->coordonee.y);
        p = p->prev;

    }
}
grille_t cree_grille(int nb_lignes,int nb_collonnes){
    grille_t g;
    g.nb_lignes = nb_lignes;
    g.nb_collonnes =nb_collonnes;
    g.grille = (cellule_t**) malloc(nb_lignes * sizeof(cellule_t*));
    for(int i=0;i<nb_lignes;i++){
        g.grille[i] = (cellule_t*) malloc ( nb_collonnes * sizeof(cellule_t));
    }

    for(int i=0;i<nb_lignes;i++){
        for(int j=0;j<nb_collonnes;j++){
        g.grille[i][j].valeur = 0;
        g.grille[i][j].modifiable = 1;
        }
    }

    return g;
}
void detruire_grille ( grille_t* g){
    for(int i=0;i<g->nb_lignes;i++){
        free(g->grille[i]);
        g->grille[i] = NULL;
    }
    free(g->grille);
    g->grille=NULL;
}

grille_t init_grille(const char* nom_fichier){
    grille_t g = cree_grille(NB_LIGNES,NB_COLLONNES);
    FILE* f = fopen(nom_fichier,"r");
    int x,y,v;
    while(fscanf(f,"%d%d%d",&x,&y,&v) != EOF){
        g.grille[x-1][y-1].valeur = v;
        g.grille[x-1][y-1].modifiable = 0;
    }

    return g;
}
void afficher_grille(grille_t g){
    printf("DEBUT AFFICHAGE\n");
    printf("-------------\n");
    for(int i=0;i<g.nb_lignes;i++){
        for(int j=0;j<g.nb_collonnes;j++){
            if(j %3 == 0)
                printf("|");
            if(g.grille[i][j].valeur == 0)
                printf(" ");
            else
                printf("%d",g.grille[i][j].valeur);
            }

        printf("|\n");
                    if((i+1)%3 == 0 && i != 0)
            printf("-------------\n");

        }

        printf("FIN AFFICHAGE\n");

    }
int combien_sur_ligne(grille_t g ,int ligne, int e){
    int cpt = 0;
    for(int j=0;j<g.nb_collonnes;j++){
        if(g.grille[ligne][j].valeur == e)
            cpt++;
    }
    return cpt;
}
int combien_sur_collonne(grille_t g ,int collonne, int e){
    int cpt = 0 ;
    for(int i=0;i<g.nb_lignes;i++){
        if(g.grille[i][collonne].valeur == e)
            cpt++;
    }
    return cpt;
}
int combien_sur_bloc (grille_t g,coordonees_t c,int e){
    int cpt = 0;
    coordonees_t c_bloc = {c.x-(c.x%3), c.y-(c.y%3)};
    for(int i=c_bloc.x ;i<c_bloc.x+3;i++){
        for(int j=c_bloc.y;j<c_bloc.y+3;j++){
            if(g.grille[i][j].valeur == e)
                cpt++;
        }
    }
    return cpt;
}
int grille_complete(grille_t g) {
    for (int i = 0; i < g.nb_lignes; i++) {
        for (int j = 0; j < g.nb_collonnes; j++) {
            if (g.grille[i][j].valeur == 0) {
                return 0; // Grille non complète
            }
        }
    }
    return 1; // Grille complète
}

void resoudre_v1 (grille_t* g,pile_coordonnees_t** p){
    while(!grille_complete(*g)){
        int trouver = 0;
        for(int i=1;i<10;i++){
            for(int j=0;j<g->nb_lignes;j++){
                for(int k=0;k<g->nb_collonnes;k++){
                    coordonees_t c = {j-(j%3), k-(k%3)};
                    if( g->grille[j][k].modifiable && g->grille[j][k].valeur == 0 && !(combien_sur_bloc(*g,c,i)) && !(combien_sur_ligne(*g,j,i)) && !(combien_sur_collonne(*g,k,i))){
                        empiler_coordonnees(p,(coordonees_t){k,j});
                        g->grille[j][k].valeur = i;
                        trouver = 1;
                    }
                if (trouver) {
                    break; 
                }
            if (trouver) {
                    break; 
            }
        }
            }
        if(!trouver){
            coordonees_t c;
            depiler_coordonnees(p, &c);
            for(int i=1;i<10;i++){
                if(i != g->grille[c.x][c.y].valeur && !(combien_sur_bloc(*g,c,i)) && !(combien_sur_ligne(*g,c.x,i)) && !(combien_sur_collonne(*g,c.y,i)))
                {
                    g->grille[c.x][c.y].valeur= i;
                    empiler_coordonnees(p,c);
                }else{
                    g->grille[c.x][c.y].valeur = 0;

                }
            }
        }
    }
    afficher_grille(*g);
    }
}
int main(){
    grille_t g = init_grille("sudoku-relax.txt");
    pile_coordonnees_t* p = NULL;
    afficher_grille(g);
    resoudre_v1(&g,&p);
    return 0;
}