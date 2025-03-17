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

    noeud_t* recherche_ABR (arbre_t A,int data){
        if(A==NULL) return NULL;
        if (A->val == data){
            return A;
        }
        if(data < A->val){
            return recherche_ABR(A->fg,data);
        }else{
            return recherche_ABR(A->fd,data);

        }
    }
    void print_node(noeud_t* n){
        if(n == NULL){
            printf("noeud vide \n");
            return;
        }
        printf("la valeur du noeud : %d\n",n->val);
    }

    arbre_t tournoi(int t[],int g,int d){
        int m = (g + d) / 2;
        arbre_t p = create_node(t[m]);
        if(g == d ) return p;
        p->fg = tournoi(t,g,m);
        p->fd = tournoi(t,m+1,d);
        int u = p->fg->val , v = p->fd->val;
        if(u>v)
            p->val = u;
        else
            p->val = v;
        return p;

    }

    void prefixe_non_recursif(arbre_t A) {
        if (A == NULL) return; // Cas de base : arbre vide

        // Taille initiale arbitraire pour éviter d'allouer trop de mémoire inutilement
        int capacite = 100;
        arbre_t* stack = (arbre_t*) malloc(capacite * sizeof(arbre_t));
        int top = -1;
        
        stack[++top] = A; // Empiler la racine

        while (top != -1) {
            arbre_t current = stack[top--]; // Dépiler
            printf("%d ", current->val);

            // Empiler d'abord le fils droit, puis le fils gauche (pour respecter l'ordre préfixe)
            if (current->fd != NULL) {
                if (top + 1 >= capacite) { // Vérifier si la pile est pleine
                    capacite *= 2;
                    stack = (arbre_t*) realloc(stack, capacite * sizeof(arbre_t));
                }
                stack[++top] = current->fd;
            }
            if (current->fg != NULL) {
                if (top + 1 >= capacite) { // Vérifier si la pile est pleine
                    capacite *= 2;
                    stack = (arbre_t*) realloc(stack, capacite * sizeof(arbre_t));
                }
                stack[++top] = current->fg;
            }
        }
        free(stack);
    }


// ICI la pile



// Repérésentation de la pile
//
//   |-|
// 3 | | 
//   |-|
// 2 | |
//   |-|
// 1 | |
//   |-|
// 0 | | <- head
//   |-|

void init_pile(pile* p){
    p->head = 0;
}

arbre_t pop(pile* p){
    if(p->head == 0) exit(1);
    return p->t[--p->head]; //si on met -- à droite, alors dans push il doit etre a gauche
}

void push(pile *p, arbre_t ptr){
    if(p->head == N-1){
        printf("La pile est pleine. Allouez plus d'espace SVP\n");
        exit(1);
    }
    p->t[p->head++]= ptr;
}

int pile_vide(pile *p){
    return p->head==0;
}

arbre_t creerNoeud(int info){
    arbre_t temp = (arbre_t)malloc(sizeof(arbre_t));
    temp->val = info;
    temp->fg = temp->fd = NULL;
    return temp;
}

void imprimer_arbre(arbre_t r, int niveau){
    //Imprimer l'arbre avec indentation niveau
    if(r != NULL){
        imprimer_arbre(r->fd, niveau+1);
        for(int i=0; i<niveau; ++i){
            printf("   ");
        }
        printf("%d\n",r->val);
        imprimer_arbre(r->fg, niveau+1);
    }
}

void prefixe_rec(arbre_t racine){
    arbre_t courant;
    pile p;
    init_pile(&p); // initialisation de pile
    courant = racine;
    if (courant != NULL){
        push(&p,courant);
        while(!pile_vide(&p)){
            courant = pop(&p);
            printf("%d ",courant->val);
            if(courant->fd != NULL)
                push(&p,courant->fd);
            if(courant->fg != NULL)
                push(&p,courant->fg);
        }
    }
}

void infixe_rec(arbre_t racine){
    arbre_t courant = racine;
    pile p;
    init_pile(&p); // initialisation de pile*
    
    while (courant != NULL || !pile_vide(&p)){
        // Parcours main fgauche
        while(courant != NULL){
            push(&p, courant);
            courant = courant ->fg;
        }
        //depiler et écrire
        courant = pop(&p);
        printf("%d ",courant->val);
        //tourner à droite
        courant = courant->fd;
        
    }
}

void postfixe_rec(arbre_t root){
    if(root == NULL) return;
    pile p1,p2;
    init_pile(&p1);
    init_pile(&p2);
    arbre_t courant;
    push(&p1,root);
    while(!pile_vide(&p1)){
        courant=pop(&p1);
        push(&p2,courant);
        if(courant->fg!=NULL){
            push(&p1,courant->fg);
        }
        if(courant->fd!=NULL){
            push(&p1,courant->fd);
        }
    }
    while(!pile_vide(&p2)){
        courant=pop(&p2);
        printf("%d ",courant->val);
    }
}

int est_tas(int tab[], int n) {
    for (int i = 0; i <= (n - 2) / 2; i++) {  // Vérifier tous les parents
        if (2 * i + 1 < n && tab[i] < tab[2 * i + 1]) return 0;  // Fils gauche
        if (2 * i + 2 < n && tab[i] < tab[2 * i + 2]) return 0;  // Fils droit
    }
    return 1;  // C'est un tas
}

void monter_tas(int tab[], int i, int valeur) {
    int x = tab[i] + valeur;  
    while (i > 0) {  
        int papa = (i - 1) / 2;
        if (tab[papa] >= x) break;

        tab[i] = tab[papa];
        i = papa;
    }
    tab[i] = x;  
}


/*
input tableau d'entiers
output Tri de Tab pas Tas
i <= n/2
*/
void descendre_tas(int tab[], int n, int i) {
    int x = tab[i];  
    int j = 2 * i + 1;  // Premier enfant (fils gauche)

    while (j < n) {  // Vérifier qu'il y a au moins un enfant
        // Vérifier si le fils droit existe et est plus grand que le fils gauche
        if (j + 1 < n && tab[j + 1] > tab[j]) {  
            j++;  // Aller au plus grand enfant
        }

        // Si la valeur actuelle est plus grande que l'enfant, on arrête
        if (x >= tab[j]) break;

        // Descendre la valeur du plus grand enfant
        tab[i] = tab[j];  
        i = j;  // Mettre `i` à la position du fils choisi
        j = 2 * i + 1;  // Calculer le prochain fils gauche
    }

    tab[i] = x;  // Placer la valeur `x` à sa position finale
}

/*
nous avons construit un TAS *
nous allons le trier
*/
void Tri_par_Tas(int tab[], int n) {
    if (n > 1) {
        int temp = tab[n - 1];
        tab[n - 1] = tab[0];
        tab[0] = temp;

        descendre_tas(tab, n - 1, 0);  

        Tri_par_Tas(tab, n - 1);
    }
}

BFS_binaire()




