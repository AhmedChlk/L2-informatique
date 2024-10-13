#include<stdio.h>

const int LIGNES_GRILLE = 10;
const int COLONNES_GRILLE = 10;
#define TAILLE_GRILLE 100

typedef enum{
    NORD,
    SUD,
    EST,
    WEST
}direction_t;

typedef struct{
    int l;
    int c;
}position_t;

typedef struct{
    position_t position_serpent[TAILLE_GRILLE]; 
    direction_t direction_serpent;
    int longueur;
}serpent_t;

void initialiser (position_t* T){
    for(int i=0;i<TAILLE_GRILLE;i++){
        T[i].l = -1;
        T[i].c = -1;
    }
}
void ajouter(position_t* T,position_t p){
    int i=0;
    while(T[i].l != -1 && T[i].c != -1)
        i++;
    if(i<TAILLE_GRILLE){
        T[i].l = p.l;
        T[i].c = p.c;
    }else{
        printf("erreur tableau deja plein de positions valide");
    }   
}
position_t retirer (position_t* T){
    position_t p = T[0];
    int i = 0;
    for(i=0;i<TAILLE_GRILLE-1;i++)
        T[i]=T[i+1];
    T[i].l = -1;
    T[i].c = -1;
    return p;
}
int appartient (position_t* T,position_t p){
    int i=0;
    while(i<TAILLE_GRILLE || (T[i].c != p.c && T[i].l != p.l))
        i++;
    if(i<TAILLE_GRILLE)
        return 1;
    else
        return -1;  

}

serpent_t creer_serpent(position_t tete_serpent, direction_t d, int longueur) {
    serpent_t serpent;
    serpent.direction_serpent = d;
    serpent.longueur =  longueur;
    initialiser(serpent.position_serpent);

    
    ajouter(serpent.position_serpent, tete_serpent);

    for (int i = 1; i < longueur; i++) {
        switch(d) {
            case SUD:
                tete_serpent.l += 1;
                break;
            case NORD:
                tete_serpent.l -= 1;
                break;
            case EST:
                tete_serpent.c += 1; 
                break;
            case WEST:
                tete_serpent.c -= 1; 
                break;
        }
        
        ajouter(serpent.position_serpent, tete_serpent);
    }

    return serpent;
}

void afficher_grille (char grille[LIGNES_GRILLE][COLONNES_GRILLE],serpent_t s) {
    for(int i = 0;i<LIGNES_GRILLE;i++){
        for(int j=0;j<COLONNES_GRILLE;j++){
            grille[i][j] = '.';
        }
    }
    for(int i = 0; i<s.longueur;i++){
        if(i == s.longueur){
            grille[s.position_serpent[i].l][s.position_serpent[i].c] = 'T';   
        }
        else{
            grille[s.position_serpent[i].l][s.position_serpent[i].c] = 'S';
        }
    }
        for(int i = 0;i<LIGNES_GRILLE;i++){
            for(int j=0;j<COLONNES_GRILLE;j++){
            printf("%c",grille[i][j]);
            }
            printf("\n");
        }
}
void avancer(serpent_t* s){
    position_t nouvelle_tete = s->position_serpent[s->longueur -1];
    int i;
         switch(s->direction_serpent) {
            case SUD:
                nouvelle_tete.l += 1;
                break;
            case NORD:
                nouvelle_tete.l -= 1;
                break;
            case EST:
                nouvelle_tete.c += 1;

                break;
            case WEST:
                nouvelle_tete.c -= 1;
                break;
        }
        for(i = 0;i<s->longueur-1;i++)
            s->position_serpent[i] = s->position_serpent[i+1];
        s->position_serpent[s->longueur - 1] = nouvelle_tete;

    }

void changer_direction(serpent_t* s,direction_t d){
    s->direction_serpent = d;
}

int main() {
    char G[LIGNES_GRILLE][COLONNES_GRILLE];
    position_t tete = {5, 5}; 
    serpent_t mon_serpent = creer_serpent(tete, SUD, 4);

    afficher_grille(G,mon_serpent);
    avancer(&mon_serpent);
    printf("avancer : NORD \n\n\n");
    afficher_grille(G,mon_serpent);
    
    changer_direction(&mon_serpent,EST);
    printf("position change a %d\n",mon_serpent.direction_serpent);
    avancer(&mon_serpent);
    printf("avancer : EST \n\n\n");
    afficher_grille(G,mon_serpent);

    

    return 0;
}
