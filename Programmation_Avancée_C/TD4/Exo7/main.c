#include <stdio.h>

int nombre_val_inferieur(int tab[],int n, int val){
    int nbr_val = 0; 
    for(int i=0;i<n;i++){
        if (tab[i] < val) nbr_val++;
    } 
    return nbr_val;
}

float moyenne_tab(int tab[],int n){
    int somme = 0 ;
    for(int i=0;i<n;i++){
        somme += tab[i];
    }
    return (float)somme / n ;
}

int min_tab(int tab[],int n){
    int mintab = tab[0];
    for(int i=1;i<n;i++){
        if(mintab> tab[i]) mintab = tab[i];
    }
    return mintab;
}

int max_tab(int tab[],int n){
    int maxtab = tab[0];
    for(int i=1;i<n;i++){
        if(maxtab< tab[i]) maxtab = tab[i];
    }
    return maxtab;
}

void lire_entier(int* var, char* chaine, char* chaine_erreur) {
    printf("%s", chaine);
    while (scanf("%d", var) != 1) {
        printf("%s\n", chaine_erreur);
        while (getchar() != '\n');
        printf("%s", chaine);
    }
}
void lire_element_tab(int* element ,char* chaine , int indice , char* chaine_erreur){
        printf("%s %d : ", chaine,indice);
    while (scanf("%d", element) != 1) {
        printf("%s\n", chaine_erreur);
        while (getchar() != '\n');
        printf("%s %d : ", chaine,indice);

    }

}

int main(){
    int n;
    lire_entier(&n,"entrez la taille du tableau : ","erreur entrez une taille de tableau valide");
    int tab[n];
    printf("entrez les valeur de votre tableau \n");
    for(int i=0;i<n;i++){
        lire_element_tab(&tab[i],"entrez la valeur de l\'element ",i+1,"erreur entrez une valeur valide");
    }

    printf("\nla valeur min du tableau : %d \n la valeur max du tableau : %d \n",min_tab(tab,n),max_tab(tab,n));
    printf("la moyenne du tableau : %f\n",moyenne_tab(tab,n));



}