#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 10
#define TAILLE_GRILLE N*N 

typedef enum{
    ND_NM,
    ND_MD,
    DV
}etat_case_t;

typedef struct {
    etat_case_t etat_case;
    int nb_mines_adjacentes;
    int contient_mine;
}case_t;

typedef struct {
    int colonnes_grille;
    int lignes_grille;
    int nbr_mines;
    int nbr_mines_decouvertes;
    case_t** grille;
}grille_demineur_t;

typedef struct{
    int l;
    int c;
}position_t;

void initialiser(int *tab){
    for(int i=0;i<TAILLE_GRILLE;i++){
        tab[i] = -1;
    }
}
void ajouter (int* tab,int p){
    int i=0;
    while(i<TAILLE_GRILLE && tab[i] != -1)
        i++;
    if(i<TAILLE_GRILLE)
        tab[i] = p;
    else
        printf("erreur tableau deja plein\n");

}

int retirer (int* tab){
    int p = tab[0],i=0;
    for(int i=0;i<TAILLE_GRILLE-1;i++)
        tab[i]=tab[i+1];
    tab[i]=-1;
    return p;
}

grille_demineur_t cree(int lignes_grille,int colonnes_grille,int nbr_mines){
    grille_demineur_t d;
    d.lignes_grille = lignes_grille;
    d.colonnes_grille = colonnes_grille;
    d.nbr_mines = nbr_mines;
    d.nbr_mines_decouvertes = 0;
    d.grille = (case_t**) malloc(lignes_grille * sizeof(case_t*));
    for(int i=0;i<lignes_grille;i++){
        d.grille[i] = (case_t*) malloc(colonnes_grille * sizeof(case_t));
    }
    return d;
}

void afficher(grille_demineur_t d) {
    // Afficher la ligne supérieure de bordure
    printf("  ");  // Pour aligner les numéros de colonne
    for (int j = 0; j < d.colonnes_grille; j++) {
        printf("%d ", j);  // Afficher les numéros de colonne
    }
    printf("\n");

    printf("  ");  // Décalage pour aligner avec les colonnes
    for (int j = 0; j < d.colonnes_grille; j++) {
        printf("――");  // Ligne supérieure de la bordure
    }
    printf("\n");

    for (int i = 0; i < d.lignes_grille; i++) {
        printf("%d|", i); 
        for (int j = 0; j < d.colonnes_grille; j++) {
            if (d.grille[i][j].etat_case == ND_NM) {
                printf("X ");
            } else if (d.grille[i][j].etat_case == ND_MD) {
                printf("F "); 
            } else if (d.grille[i][j].etat_case == DV) {
                if (d.grille[i][j].contient_mine) {
                    printf("* ");
                } else if (d.grille[i][j].nb_mines_adjacentes == 0) {
                    printf("  "); 
                } else {
                    printf("%d ", d.grille[i][j].nb_mines_adjacentes);
                }
            }
        }
        printf("|\n");
    }

    printf("  ");
    for (int j = 0; j < d.colonnes_grille; j++) {
        printf("――");
    }
    printf("\n");
}

void initialiser_tab_traitement(int tab[N][N] ){
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            tab[i][j] = 0;
        }
    }
} 

void devoiler_case_vide(grille_demineur_t *d, int pos_x, int pos_y) {
    int tab_x[TAILLE_GRILLE];
    int tab_y[TAILLE_GRILLE];
    int traitee[N][N];  
    int x, y;

    initialiser(tab_x);
    initialiser(tab_y);
    initialiser_tab_traitement(traitee);

    ajouter(tab_x, pos_x);
    ajouter(tab_y, pos_y);
    traitee[pos_x][pos_y] = 1;

    while (!(tab_x[0] == -1 && tab_y[0] == -1)) {
        x = retirer(tab_x);
        y = retirer(tab_y);
        d->grille[x][y].etat_case = DV;
        for (int k = -1; k <= 1; k++) {
            for (int l = -1; l <= 1; l++) {
                int nx = x + k;
                int ny = y + l;
                if (nx >= 0 && nx < d->lignes_grille && ny >= 0 && ny < d->colonnes_grille && !traitee[nx][ny]) {
                    if (d->grille[nx][ny].etat_case == ND_NM && d->grille[nx][ny].contient_mine == 0) {
                        d->grille[nx][ny].etat_case = DV;
                        traitee[nx][ny] = 1;
                        if (d->grille[nx][ny].nb_mines_adjacentes == 0) {
                            ajouter(tab_x, nx);
                            ajouter(tab_y, ny);
                        }
                    }
                }
            }
        }
    }
}
void placer_drapeau(grille_demineur_t *d , int pos_x , int pos_y){
    d->grille[pos_x][pos_y].etat_case = ND_MD;
    if(d->grille[pos_x][pos_y].contient_mine){
        d->nbr_mines_decouvertes++;
    }
}

void placer_mines_apres_premier_coup(grille_demineur_t* d, int premier_x, int premier_y) {
    int mines_placees = 0;
    while (mines_placees < d->nbr_mines) {
        int l = rand() % d->lignes_grille;
        int c = rand() % d->colonnes_grille;
        if (!d->grille[l][c].contient_mine && (abs(l - premier_x) > 1 || abs(c - premier_y) > 1)){

            d->grille[l][c].contient_mine = 1;
            mines_placees++;
        }
    }

    for (int i = 0; i < d->lignes_grille; i++) {
        for (int j = 0; j < d->colonnes_grille; j++) {
            if (!d->grille[i][j].contient_mine) {
                d->grille[i][j].nb_mines_adjacentes = 0;
                for (int k = -1; k <= 1; k++) {
                    for (int l = -1; l <= 1; l++) {
                        int ni = i + k;
                        int nj = j + l;
                        if ((k != 0 || l != 0) && ni >= 0 && ni < d->lignes_grille && nj >= 0 && nj < d->colonnes_grille) {
                            if (d->grille[ni][nj].contient_mine) {
                                d->grille[i][j].nb_mines_adjacentes++;
                            }
                        }
                    }
                }
            }
        }
    }
    devoiler_case_vide(d,premier_x,premier_y);
}
void lire_coordonee (int* x , int* y){
        printf("entrez le x : ");
    while(scanf("%d",x) != 1 || *x > N || *x < 0 ){
        printf("erreur entrez une valeur de x valide \n");
        printf("entrez le x : ");
        while(getchar() != '\n');
    }
    printf("entrez le y : ");
    while(scanf("%d",y) != 1 || *y > N || *y < 0 ){
        printf("erreur entreez une valeur de y valide \n");
        printf("entrez le y : ");
        while(getchar() != '\n');
    }
}
int check_win(grille_demineur_t d){
    if(d.nbr_mines_decouvertes == d.nbr_mines)
        return 1;
    else
        return 0;  
}
void affichage_grille_devoilee(grille_demineur_t d){
    for (int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            d.grille[i][j].etat_case = DV;
        }
    }
}
int main() {
    srand(time(NULL));
    int x,y,perdue = 0,choix;
    grille_demineur_t D = cree(N, N, 1);
    printf("entrez la premiere case a devoiler pour debuter a jouer");
    lire_coordonee(&x,&y);
    placer_mines_apres_premier_coup(&D,x,y);
    while(!perdue && !check_win(D)){
        afficher(D);
        printf("choisissez que faire : \n"
                "1 : placer un drapeau \n"
                "2 : devoiler une case \n");
        while(scanf("%d",&choix) != 1 || choix < 1 || choix > 2 )
        printf("erreur entrez un choix valide \n");
        printf("choisissez que faire : \n"
                "1 : placer un drapeau \n"
                "2 : devoiler une case \n");
        while(getchar() != '\n');
        lire_coordonee(&x,&y);
        switch(choix){
            case 1:
                placer_drapeau(&D,x,y);
                break;
            case 2:
                if(D.grille[x][y].contient_mine){
                    printf("vous avez perdue\n");
                    affichage_grille_devoilee(D);
                    perdue = 1;
                    break;
                }
                else{
                    devoiler_case_vide(&D,x,y);
                    break;
                }
        }
        
    }
    if(check_win(D)){
        printf("vous avez gagner\n");
        affichage_grille_devoilee(D);

    }

    afficher(D);
    for (int i = 0; i < D.lignes_grille; i++) {
        free(D.grille[i]);
    }
    free(D.grille);

    return 0;
}
