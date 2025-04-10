#include<stdio.h>
#include<stdlib.h>

#define NB_LIGNES 9
#define NB_COLLONNES 9 

typedef struct liste_entier_t{
    int val;
    struct liste_entier_t* next;
    struct liste_entier_t* prev;
}liste_entier_t;
typedef struct {
    int valeur;
    int modifiable;
    struct liste_entier_t* liste_entier;
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
int appartient_pile_coordonnees(pile_coordonnees_t* p ,coordonees_t c ){
    // Parcourt la pile jusqu'à ce qu'on trouve un élément correspondant à c.x, c.y
    // ou jusqu'à ce qu'elle soit vide.
    while (p != NULL && (p->coordonee.x != c.x || p->coordonee.y != c.y)) {
        p = p->prev;
    }
    return (p != NULL); // Si p n'est pas NULL, c'est qu'on a trouvé la coordonnée.
}

void detruire_pile_coordonnees(pile_coordonnees_t** p){
    if(*p == NULL)
        return;
    while((*p)->prev != NULL){
        pile_coordonnees_t* temp = *p;
        (*p) = (*p)->prev;
        free(temp);
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
        printf("(%d,%d) ",p->coordonee.x,p->coordonee.y);
        p = p->prev;

    }
    printf("\n");
}

int longueur_liste_entier (liste_entier_t* l){
    if(l == NULL)
        return 0;
    else
        return 1 + longueur_liste_entier(l->next);
}

void afficher_liste_entier (liste_entier_t* l){
    printf("liste entiers : ");
    while(l != NULL){
        printf("%d ",l->val);
        l = l->next;
    }
    printf("\n");
}
coordonees_t rechercher_meilleure_cellule(grille_t g, pile_coordonnees_t* p) {
    int i = 0, j = 0;
    coordonees_t c_min;

    // Trouver la première cellule qui n'est pas dans la pile
    while (i < g.nb_lignes && appartient_pile_coordonnees(p, (coordonees_t){i, j})) {
        j++;
        if (j == g.nb_collonnes) {
            j = 0;
            i++;
        }
    }

    if (i == g.nb_lignes) {
        // Au cas où toutes les cellules appartiennent déjà à la pile (cas extrême)
        c_min.x = c_min.y = -1;
        return c_min;
    }

    int longueur_min = longueur_liste_entier(g.grille[i][j].liste_entier);
    c_min.x = i;
    c_min.y = j;

    // On passe à la cellule suivante
    j++;
    if (j == g.nb_collonnes) {
        j = 0;
        i++;
    }

    // Parcourir le reste de la grille
    while (i < g.nb_lignes) {
        if (!appartient_pile_coordonnees(p, (coordonees_t){i, j})) {
            int current_length = longueur_liste_entier(g.grille[i][j].liste_entier);
            if (current_length < longueur_min) {
                longueur_min = current_length;
                c_min.x = i;
                c_min.y = j;
            }
        }
        // Passer à la cellule suivante
        j++;
        if (j == g.nb_collonnes) {
            j = 0;
            i++;
        }
    }

    return c_min;
}

void inserer_en_tete_entier (liste_entier_t** l,int val){
    liste_entier_t* m = (liste_entier_t*) malloc(sizeof(liste_entier_t));
    m->val = val;
    m->prev = NULL;
    m->next = *l;
    if(*l != NULL)
        (*l)->prev = m;
    *l = m;
}
liste_entier_t* recherche_entier (liste_entier_t* l, int val){
    while(l != NULL){
        if(l->val == val )
            return l;
        else
            l = l->next;
    }
    return NULL;
}


void supprimer_entier(liste_entier_t** l, int val) {
    if (l == NULL || *l == NULL) {
        return;
    }

    liste_entier_t* current = *l;

    while (current != NULL && current->val != val) {
        current = current->next;
    }

    if (current == NULL) {
        return;
    }

    if (current->prev != NULL) {
        current->prev->next = current->next;
    } else {
        *l = current->next;
    }

    if (current->next != NULL) {
        current->next->prev = current->prev;
    }

    free(current);
}

void detruire_liste_entier(liste_entier_t** l){
    while(*l != NULL){
        liste_entier_t* temp = *l;
        *l = (*l)->next;
        free(temp);
    }
    l = NULL;
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
        g.grille[i][j].liste_entier = NULL;
        }
    }

    return g;
}
void detruire_grille ( grille_t* g){
    for(int i=0;i<g->nb_lignes;i++){
        for(int j=0;j<g->nb_collonnes;j++){
            detruire_liste_entier(&(g->grille[i][j].liste_entier));
        }
        free(g->grille[i]);
        g->grille[i] = NULL;
    }
    free(g->grille);
    g->grille=NULL;
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









int insertion_valide (grille_t g,coordonees_t c,int val){
    return (!(combien_sur_bloc(g,c,val)) && !(combien_sur_ligne(g,c.x,val)) && !(combien_sur_collonne(g,c.y,val)));
}
grille_t init_grille(const char* nom_fichier){
    grille_t g = cree_grille(NB_LIGNES,NB_COLLONNES);
    FILE* f = fopen(nom_fichier,"r");
    int x,y,v;
    while(fscanf(f,"%d%d%d",&x,&y,&v) != EOF){
        g.grille[x-1][y-1].valeur = v;
        g.grille[x-1][y-1].modifiable = 0;
    }
    for(int i=0;i<g.nb_lignes;i++){
        for(int j=0;j<g.nb_collonnes;j++){
            for(int val=1;val<10;val++){
                if(g.grille[i][j].modifiable && insertion_valide(g,(coordonees_t){i,j},val))
                    inserer_en_tete_entier(&(g.grille[i][j].liste_entier),val);
            }
        }
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
                if (g.grille[i][j].modifiable)
                    //\033[31;1;4mHello\033[0m
                    printf("\033[31m%d\033[0m",g.grille[i][j].valeur);
                else
                    printf("%d",g.grille[i][j].valeur);
            }

        printf("|\n");
                    if((i+1)%3 == 0 && i != 0)
            printf("-------------\n");

        }

        printf("FIN AFFICHAGE\n");

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
void resoudre_v1 (grille_t* g){
    int i=0,j=0,cpt_tour = 0;
    pile_coordonnees_t* p = creer_pile_coordonnees();
    while(!grille_complete(*g)){
        if(g->grille[i][j].modifiable){
            int val=g->grille[i][j].valeur;
            while(val<=9 && !insertion_valide(*g,(coordonees_t){i,j},val))
                val++;
            if(val <= 9)
            {
                g->grille[i][j].valeur = val;
                empiler_coordonnees(&p,(coordonees_t){i,j});
                if(j<g->nb_collonnes)
                    j++;
                else
                {
                    i++;
                    j=0;
                }
            }else{
                if(p == NULL ){
                    printf("erreur grille impossible a resoudre");
                    return;
                }
                coordonees_t c;
                g->grille[i][j].valeur = 0;
                depiler_coordonnees(&p,&c);
                i=c.x;
                j=c.y;
            }
        }else{
            if(j<g->nb_collonnes)
                j++;
            else
            {
                i++;
                j=0;
            }
        }
    cpt_tour++;
    }
    printf("nombre tours pour resoudre la grille sur la v1 : %d \n",cpt_tour);
    detruire_pile_coordonnees(&p);

}
void resoudre_v2(grille_t* g){
    pile_coordonnees_t* p = creer_pile_coordonnees();
    int i=0,j=0,cpt_tour = 0;
    while(!grille_complete(*g)){
        if(g->grille[i][j].modifiable){
            liste_entier_t* temp = g->grille[i][j].liste_entier;
            while(temp != NULL && temp->val < g->grille[i][j].valeur && !insertion_valide(*g,(coordonees_t){i,j},temp->val))
            {
                temp = temp->next;
            }
            if(temp != NULL){
                g->grille[i][j].valeur = temp->val;
                empiler_coordonnees(&p,(coordonees_t){i,j});
                if(j<g->nb_collonnes)
                    j++;
                else{
                    i++;
                    j=0;
                }
            }
            else{
                if(p == NULL ){
                    printf("erreur grille impossible a resoudre");
                    return;
                }
                coordonees_t c;
                depiler_coordonnees(&p,&c);
                g->grille[i][j].valeur = 0;
                i = c.x;
                j = c.y;
            }
        }
        else{
            if(j<g->nb_collonnes)
                j++;
            else{
                i++;
                j=0;
            }
        }
    cpt_tour++;
    }
    printf("nombre tours pour resoudre la grille sur la v2 : %d \n",cpt_tour);
    detruire_pile_coordonnees(&p);
}
void resoudre_v3(grille_t* g) {
    pile_coordonnees_t* p = creer_pile_coordonnees();
    int cpt_tour = 0;
    
    while(!grille_complete(*g)) {
        coordonees_t min_coup = rechercher_meilleure_cellule(*g, p);
        if(min_coup.x == -1 && min_coup.y == -1) {
            // Aucune cellule à traiter => impossible
            printf("erreur grille impossible a resoudre\n");
            detruire_pile_coordonnees(&p);
            return;
        }

        int i = min_coup.x;
        int j = min_coup.y;
        liste_entier_t* temp = g->grille[i][j].liste_entier;
        int current_val = g->grille[i][j].valeur;

        // On cherche un candidat valide supérieur à la valeur actuelle
        while(temp != NULL && (temp->val <= current_val || !insertion_valide(*g,(coordonees_t){i,j},temp->val))) {
            temp = temp->next;
        }

        if(temp != NULL) {
            // On a trouvé une valeur possible
            g->grille[i][j].valeur = temp->val;
            empiler_coordonnees(&p,(coordonees_t){i,j});
        } else {
            // Pas de solution depuis cet état, on backtrack
            if(p == NULL) {
                printf("erreur grille impossible a resoudre\n");
                detruire_pile_coordonnees(&p);
                return;
            }
            coordonees_t c;
            depiler_coordonnees(&p,&c);
            g->grille[c.x][c.y].valeur = 0;
        }

        cpt_tour++;
    }

    printf("nombre tours pour resoudre la grille sur la v3 : %d \n", cpt_tour);
    detruire_pile_coordonnees(&p);
}

int main(){
    grille_t g = init_grille("sudoku-relax.txt");
    resoudre_v3(&g);

    return 0;
}