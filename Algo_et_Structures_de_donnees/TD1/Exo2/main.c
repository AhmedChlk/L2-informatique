#include <stdio.h>
#include <stdlib.h>

typedef struct liste_t {
    int val_fils;
    struct liste_t* next;
}liste_t;

typedef struct{
    liste_t** tab_fils;
    int n;
}arbre_t;

liste_t* cree_noeud(int val){
    liste_t* new = (liste_t*) malloc(sizeof(liste_t));
    new->val_fils = val;
    new->next = NULL;
    return new;
}
arbre_t cree_arbre(void){
    arbre_t A;
    int val = -2;
    printf("entrez la taille de votre arbre : ");
    while(scanf("%d",&A.n) != 1 && A.n < 1){
        printf("erreur entrez une valeur valide pour la creation \n");
        printf("entrez la taille de votre arbre : ");
        while(getchar() != '\n');
    }
    A.tab_fils = (liste_t**) malloc(A.n * sizeof(liste_t*));
    for(int i=0;i<A.n;i++){
        A.tab_fils[i] = NULL;
        printf("entrez les fils du noeud et tapez -1 pour arreter l'insertion des fils du noeud %d ",i);
        do{
            while(scanf("%d",&val) != 1 || val < -1){
                printf("erreur entrez une valeur valide\n");
                printf("entrez les fils du noeud et tapez -1 pour arreter l'insertion des fils du noeud %d ",i);
            }
            if(val != -1){
                if(A.tab_fils[i] == NULL){
                    A.tab_fils[i] = cree_noeud(val); 
                }
                else
                {
                liste_t* temp = A.tab_fils[i];
                while( temp->next != NULL){
                    temp = temp->next;
                }
                temp->next = cree_noeud(val);   
                }
 
            }

        }while(val != -1);
    }
    return A;
}

void afficher_liste_enfants(liste_t* l){
    while(l != NULL){
        printf("%d ", l->val_fils);
        l = l->next;
    }
}
void afficher_arbre(arbre_t A){
    for(int i=0;i<A.n;i++){
        printf("les enfants de %d sont : ",i);
        afficher_liste_enfants(A.tab_fils[i]);
        printf("\n");
    }
}

int main(void){
    arbre_t A = cree_arbre();
    afficher_arbre(A);
}