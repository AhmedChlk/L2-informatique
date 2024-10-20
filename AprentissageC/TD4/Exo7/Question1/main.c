#include <stdio.h>
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

    printf("\nla valeur min du tableau : %d \n la valeur max du tableau : %d ",min_tab(tab,n),max_tab(tab,n));

}