#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define TAILLE_GRILLE 1800
#define NOMBRE_POMMES 6
#define LONGUEUR_OBSTACLES 4

const int NOMBRE_OBSTACLES = 6;
const int LIGNES_GRILLE = 60;
const int COLONNES_GRILLE = 30;

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

typedef struct{
    position_t pos[LONGUEUR_OBSTACLES];
    direction_t direction;
    int longueur;
}obstacle_t;

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

void afficher_grille (char grille[LIGNES_GRILLE][COLONNES_GRILLE],serpent_t s,position_t* pommes ,obstacle_t* obstacles ) {
    for(int i = 0;i<LIGNES_GRILLE;i++){
        for(int j=0;j<COLONNES_GRILLE;j++){
            grille[i][j] = '.';
        }
    }
    for(int i = 0; i<s.longueur;i++){
        if(i == s.longueur -1){
            grille[s.position_serpent[i].l][s.position_serpent[i].c] = '+';   
        }
        else{
            grille[s.position_serpent[i].l][s.position_serpent[i].c] = '*';
        }
    }
    for(int i = 0; i<NOMBRE_POMMES;i++){
            grille[pommes[i].l][pommes[i].c] = 'o';   
    }

    for(int i=0;i<NOMBRE_OBSTACLES;i++){
        for(int j = 0;j<LONGUEUR_OBSTACLES;j++){
            grille[obstacles[i].pos[j].l][obstacles[i].pos[j].c] = 'X';
        }
    }
        for(int i = 0;i<LIGNES_GRILLE;i++){
            for(int j=0;j<COLONNES_GRILLE;j++){
            printf(" %c ",grille[i][j]);
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
void creer_pommes (position_t* pommes){
    
    for(int i=0;i<NOMBRE_POMMES;i++){
        pommes[i].l = rand() % LIGNES_GRILLE;
        pommes[i].c = rand() % COLONNES_GRILLE; 
    }
}

int manger(serpent_t s,position_t* pommes){
    int i=0;
    while(i<NOMBRE_POMMES && ((s.position_serpent[s.longueur-1].c != pommes[i].c) || (s.position_serpent[s.longueur-1].l != pommes[i].l) )){
        i++;
    }
    if(i<NOMBRE_POMMES){
        pommes[i].l = rand() % LIGNES_GRILLE;
        pommes[i].c = rand() % COLONNES_GRILLE;
        return 1;
    }
    else
        return 0;
}
void redimensionner_serpent(serpent_t*s){
    int l=0;
    int c=0;
    switch(s->direction_serpent){
        case SUD:
                l = 1;
                break;
        case NORD:
                l = -1;
                break;
        case EST:
                c = 1;
                break;
        case WEST:
                c = -1;
                break;
    }
    position_t p = {s->position_serpent[s->longueur - 1].l + l,s->position_serpent[s->longueur - 1].c + c};
    ajouter(s->position_serpent,p);
    s->longueur++;
    
}

void initialiser_obstacle (position_t* T){
    for(int i=0;i<LONGUEUR_OBSTACLES;i++){
        T[i].l = -1;
        T[i].c = -1;
    }
}

obstacle_t cree_obstacle(position_t p,direction_t d,int longueur){
    obstacle_t ob;
    ob.longueur = longueur;
    ob.direction = d;
    initialiser_obstacle(ob.pos);
    ajouter(ob.pos,p);
    for(int i=0;i<longueur-1;i++){
        switch(d){
            case SUD:
                p.l += 1;
                break;
        case NORD:
                p.l -= 1;
                break;
        case EST:
                p.c += 1;
                break;
        case WEST:
                p.c -= 1;
                break;
        }
        ajouter(ob.pos,p);
    }
    return ob;
}


void cree_obstacles (obstacle_t* obstacles){
    for(int i=0;i<NOMBRE_OBSTACLES;i++){
        direction_t d;
        position_t p;
        p.l = rand() % LIGNES_GRILLE;
        p.c = rand() % COLONNES_GRILLE;
        switch(rand() % 4){
            case 0:
                d = NORD;
                break;
            case 1:
                d = SUD;
                break;
            case 2:
                d = EST;
                break;
            case 3: 
                d = WEST;
                break;
        }
        obstacles[i] = cree_obstacle(p,d,LONGUEUR_OBSTACLES);
        
    }
}
int percuter(obstacle_t* obstacles,serpent_t s){
    int i=0;
    while(i<NOMBRE_OBSTACLES ){
        for(int j=0 ; j<LONGUEUR_OBSTACLES;j++){
            if((obstacles[i].pos[j].l == s.position_serpent[s.longueur -1].l )&& (obstacles[i].pos[j].c == s.position_serpent[s.longueur -1].c ) )
                return 1;
        }
        i++;
    }
    if(s.position_serpent[s.longueur -1].l>=LIGNES_GRILLE || s.position_serpent[s.longueur -1].l < 0 || s.position_serpent[s.longueur -1].c >= COLONNES_GRILLE || s.position_serpent[s.longueur -1].c < 0)
        return 1;
    for(int k=0;k<s.longueur-1;k++){
        if(s.position_serpent[k].l == s.position_serpent[s.longueur-1].l && s.position_serpent[k].c == s.position_serpent[s.longueur-1].c)
            return 1;
    }
    return 0;


}
int main() {
    srand(time(NULL));
    obstacle_t obstacles[NOMBRE_OBSTACLES];
    cree_obstacles(obstacles);
    char G[LIGNES_GRILLE][COLONNES_GRILLE];
    position_t tete = {5, 5}; 
    serpent_t mon_serpent = creer_serpent(tete, SUD, 4);
    position_t pommes[NOMBRE_POMMES];
    creer_pommes(pommes);
    int choix;
    while(!percuter(obstacles,mon_serpent)){
        afficher_grille(G,mon_serpent,pommes,obstacles);
        printf("entrez la direction ou vous voulez patir : (0 pour SUD, 1 pour NORD , 2 pour EST , 3 pour WEST ) ");
        scanf("%d",&choix);
        while(getchar()!= '\n');
        switch(choix){
            case 0:
                changer_direction(&mon_serpent,SUD);
                break;
            case 1:
                changer_direction(&mon_serpent,NORD);
                break;
            case 2:
                changer_direction(&mon_serpent,EST);
                break;
            case 3:
                changer_direction(&mon_serpent,WEST);
                break;
            default:
                printf("entrez un choix valide\n");
                break;
        }
         avancer(&mon_serpent);
        if(manger(mon_serpent,pommes)){
            redimensionner_serpent(&mon_serpent);
        }

    }
    printf("partie terminé \n");

    return 0;
}
