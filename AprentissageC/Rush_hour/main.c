#include <stdio.h>
#include <stdlib.h>

#define NBR_VEC 16
#define NBR_CONF 20
#define LIGNES_GRILLE 6
#define COLONNES_GRILLE 6

typedef enum {
    GAUCHE,
    DROITE,
    HAUT,
    BAS
} direction_t;

typedef enum {
    HORIZONTAL,
    VERTICAL
} orientation_t;

typedef struct {
    int x,y;
} coordonnee_t;

typedef struct {
    coordonnee_t pos_vec;   // position de la case la plus à gauche (si horizontal) ou la plus haute (si vertical)
    orientation_t orient_vecs;
    char nom_vec;
    int longueur_vec;
} vehicule_t;

typedef struct {
    int vehicule_ind;
    direction_t direc_mouv;
    int longueur_mouv;
} mouvement_t;

typedef struct {
    vehicule_t tab_vec[NBR_VEC];
    int prec;
    mouvement_t mouv_conf;
} configuration_t;

typedef struct {
    configuration_t* tab_config;
    int current, max, size, nbr_vec;
} rush_hour_t;

typedef struct {
    char tab_grille[LIGNES_GRILLE][COLONNES_GRILLE];
} grille_t;


void increase_size(rush_hour_t* r,int n){
    r->size += n;
    r->tab_config = (configuration_t*) realloc(r->tab_config,(r->size) * sizeof(configuration_t));
    if(r->tab_config == NULL){
        fprintf(stderr,"Erreur reallocation\n");
        exit(EXIT_FAILURE);
    }
}

rush_hour_t* allocate(const char* nom_fichier){
    int i = 0;
    rush_hour_t* r =  (rush_hour_t*)malloc(sizeof(rush_hour_t));
    if(!r){
        fprintf(stderr,"Erreur allocation rush_hour_t\n");
        exit(EXIT_FAILURE);
    }

    r->size = NBR_CONF;
    r->current = 0;
    r->max = 0;
    r->nbr_vec = 0;

    r->tab_config = (configuration_t*) malloc(NBR_CONF * sizeof(configuration_t));
    if(!r->tab_config){
        fprintf(stderr,"Erreur allocation tab_config\n");
        exit(EXIT_FAILURE);
    }

    // Mouvement initial factice pour la configuration initiale (pas de prédécesseur)
    mouvement_t m = {-1, GAUCHE, 0};
    r->tab_config[0].prec = -1;
    r->tab_config[0].mouv_conf = m;

    FILE* F = fopen(nom_fichier,"r");
    if(F == NULL){
        fprintf(stderr,"Erreur ouverture fichier %s\n", nom_fichier);
        exit(EXIT_FAILURE);
    }

    coordonnee_t c;
    int longueur;
    char nom, orientation;
    while(fscanf(F,"%d %d %d %c %c",&c.x,&c.y,&longueur,&orientation,&nom) != EOF && i < NBR_VEC){
        r->tab_config[0].tab_vec[i].pos_vec.x = c.x;
        r->tab_config[0].tab_vec[i].pos_vec.y = c.y;
        r->tab_config[0].tab_vec[i].nom_vec = nom;
        r->tab_config[0].tab_vec[i].longueur_vec = longueur;
        switch(orientation){
            case 'h' : 
                r->tab_config[0].tab_vec[i].orient_vecs = HORIZONTAL;
                break;  
            case 'v' :
                r->tab_config[0].tab_vec[i].orient_vecs = VERTICAL;
                break;
            default:
                fprintf(stderr,"Orientation inconnue : %c\n", orientation);
                fclose(F);
                exit(EXIT_FAILURE);
        }
        i++;
    }
    fclose(F);

    // Mettre a jour le nombre réel de véhicules lus
    r->nbr_vec = i;

    return r;   
}

void desalouer (rush_hour_t** r){
    if(r && *r){
        free((*r)->tab_config);
        (*r)->tab_config = NULL;
        free(*r);
        *r = NULL;
    }
}

grille_t cree_grille (rush_hour_t* r){
    grille_t g;
    // Initialisation du tableau
    for(int i=0;i<LIGNES_GRILLE;i++){
        for(int j=0;j<COLONNES_GRILLE;j++){
            g.tab_grille[i][j] = '.';
        }
    }

    // Placer les véhicules
    for(int i=0; i<r->nbr_vec; i++){
        vehicule_t v = r->tab_config[r->current].tab_vec[i];
        coordonnee_t c = v.pos_vec;
        for(int j=0;j<v.longueur_vec;j++){
            g.tab_grille[c.x][c.y] = v.nom_vec;
            if(v.orient_vecs == VERTICAL) {
                c.x++;
            } else {
                c.y++;
            }
        }
    }
    return g;
}
void print(rush_hour_t* r){
    grille_t g = cree_grille(r);

    // Affichage avec bordures
    printf("+------+\n");
    for(int i=0; i<LIGNES_GRILLE; i++){
        printf("|");
        for(int j=0; j<COLONNES_GRILLE; j++){
            printf("%c", g.tab_grille[i][j]);
        }
        printf("|\n");
    }
    printf("+------+\n");
}


configuration_t* move(rush_hour_t* r,int k,direction_t d,int l){
    grille_t g = cree_grille(r);
    configuration_t* conf = (configuration_t*) malloc(sizeof(configuration_t));
    conf->prec = r->current;
    mouvement_t m = {k,d,l};
    conf->mouv_conf = m;
    for(int i=0;i<NBR_VEC;i++){
        conf->tab_vec[i] = r->tab_config[r->current].tab_vec[i];
    }
    coordonnee_t c = r->tab_config[r->current].tab_vec[k].pos_vec;
        if(r->tab_config[r->current].tab_vec[k].orient_vecs == HORIZONTAL && (d == GAUCHE  || d == DROITE)){
            if(d == DROITE){
                c.y += r->tab_config[r->current].tab_vec[k].longueur_vec;
                for(int i=0;i<l;i++){
                    if(c.y + i < COLONNES_GRILLE ){
                        if (g.tab_grille[c.x][c.y +i] != '.')
                            return NULL;
                    }else
                        return NULL;
                }
                conf->tab_vec[k].pos_vec.y += l;
            }
            else{
                c.y -= 1;
                for(int i=0;i<l;i++){
                    if(c.y - i >= 0 ){
                        if(g.tab_grille[c.x][c.y - i] != '.')
                            return NULL;
                    }
                    else 
                        return NULL;
                }
                conf->tab_vec[k].pos_vec.y -= l;

            }
        }else if (r->tab_config[r->current].tab_vec[k].orient_vecs == VERTICAL && (d == HAUT  || d == BAS)){
            if(d == BAS){
                c.x += r->tab_config[r->current].tab_vec[k].longueur_vec;
                for(int i=0;i<l;i++){
                    if(c.x + i < LIGNES_GRILLE ){
                        if(g.tab_grille[c.x + i][c.y] != '.')
                            return NULL;
                    }else
                        return NULL;
                }
                conf->tab_vec[k].pos_vec.x += l;
            }
            else{
                c.x -= 1;
                for(int i=0;i<l;i++){
                    if(c.x - i >= 0 ){
                        if(g.tab_grille[c.x - i][c.y] != '.')
                            return NULL;                    
                    }else
                        return NULL;
                 }
                conf->tab_vec[k].pos_vec.x -= l;
            }

        }
        else{
            return NULL;
        }
    return conf;

}
int configurations_egales (const configuration_t* c1, const configuration_t* c2, int nbr_vec){
    for(int i = 0; i < nbr_vec; i++){
        if(c1->tab_vec[i].pos_vec.x != c2->tab_vec[i].pos_vec.x ||
           c1->tab_vec[i].pos_vec.y != c2->tab_vec[i].pos_vec.y ||
           c1->tab_vec[i].orient_vecs != c2->tab_vec[i].orient_vecs ||
           c1->tab_vec[i].nom_vec != c2->tab_vec[i].nom_vec ||
           c1->tab_vec[i].longueur_vec != c2->tab_vec[i].longueur_vec){
                return 0; // Les configurations ne sont pas égales
           }
    }
    return 1; // Les configurations sont égales
}
int existance_conf(rush_hour_t* r , configuration_t* conf){
    for(int i = 0; i <= r->max; i++){ // Inclure r->max
        if(configurations_egales(&r->tab_config[i], conf, r->nbr_vec))
            return 1;
    }
    return 0;
}



void print_moves (rush_hour_t* r){
    int indice = r->current;
    while(indice != -1){
        printf("%d %d %d \n",r->tab_config[indice].mouv_conf.vehicule_ind,r->tab_config[indice].mouv_conf.direc_mouv,r->tab_config[indice].mouv_conf.longueur_mouv);
        indice = r->tab_config[indice].prec;
    } 
    
}

int is_on_cell(configuration_t conf, int nbr_vec){
    for(int i = 0; i < nbr_vec; i++){
        if(conf.tab_vec[i].nom_vec == 'X'){
            if(conf.tab_vec[i].pos_vec.x == 2 && conf.tab_vec[i].pos_vec.y == 4){
                return 1; // Configuration gagnante
            } else {
                return 0; // Véhiculé 'X' trouvé mais pas en position de sortie
            }
        }
    }
    printf("Erreur : le véhicule de sortie 'X' n'a pas été trouvé.\n");
    return -1; // 'X' non trouvé
}
grille_t cree_grille_conf (configuration_t* conf,int nbr_vec){
    grille_t g;
    // Initialisation du tableau
    for(int i=0;i<LIGNES_GRILLE;i++){
        for(int j=0;j<COLONNES_GRILLE;j++){
            g.tab_grille[i][j] = '.';
        }
    }

    // Placer les véhicules
    for(int i=0; i< nbr_vec; i++){
        vehicule_t v = conf->tab_vec[i];
        coordonnee_t c = v.pos_vec;
        for(int j=0;j<v.longueur_vec;j++){
            g.tab_grille[c.x][c.y] = v.nom_vec;
            if(v.orient_vecs == VERTICAL) {
                c.x++;
            } else {
                c.y++;
            }
        }
    }
    return g;
}
void print_conf(configuration_t* conf,int nbr_vec){
    grille_t g = cree_grille_conf(conf,nbr_vec);

    // Affichage avec bordures
    printf("+------+\n");
    for(int i=0; i<LIGNES_GRILLE; i++){
        printf("|");
        for(int j=0; j<COLONNES_GRILLE; j++){
            printf("%c", g.tab_grille[i][j]);
        }
        printf("|\n");
    }
    printf("+------+\n");
}
void generate_configurations(rush_hour_t* r){
    direction_t tab_dir[4] = {HAUT, BAS, GAUCHE, DROITE};
    
    for(int j = 0; j < r->nbr_vec; j++){
        for(int i = 0; i < 4; i++){
            for(int k = 1; k < COLONNES_GRILLE - 1; k++){
                configuration_t* conf = move(r, j, tab_dir[i], k);
                if(conf != NULL && !existance_conf(r, conf)){
                    if(r->max == r->size - 1){
                        increase_size(r, 10);
                        printf("Réallocation : nouvelle taille = %d\n", r->size);
                    }
                    r->max++;
                    r->tab_config[r->max] = *conf;
                }
                else if(conf != NULL){
                    free(conf); // Libérer la mémoire si la configuration existe déjà
                }
            }
        }
    }
}

int main(void){
    rush_hour_t* r = allocate("rush1.txt");
    while(!is_on_cell(r->tab_config[r->current],r->nbr_vec)){
        generate_configurations(r);
        r->current++;
    }
    print_moves(r);
    return 0;
}
