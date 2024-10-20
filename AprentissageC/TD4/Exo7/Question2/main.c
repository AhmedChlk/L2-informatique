#include <stdio.h>
float moyenne_tab(tab[],n){
    int somme = 0 ;
    for(int i=0;i<n;i++) somme += tab[i];
    return somme / n ;
}
int main(){
    int n;
    printf("entrez la taille de votre tableau : ");
    while(scanf("%d",&n) != 1){
        printf("erreur entrez une taille valide\n");
        printf("entrez la taille de votre tableau : ");
        while(getchar() != '\n');
    }
    int tab[n];
    printf("entrez les valeur de votre tableau \n");
    for(int i=0;i<n;i++){
        printf("entrez l'element %d du tableau : ",i+1);
        while(scanf("%d",&tab[i]) != 1){
        printf("erreur entrez une taille valide\n");
        printf("entrez l'element %d du tableau : ",i+1);
        }
    }

    printf("\nla valeur moyenne du tableau : %f \n ",moyenne_tab(tab,n));

}