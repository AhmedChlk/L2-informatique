#include<stdio.h>

void ligne_etoile (int n){
    for(int i=0;i<n;i++){
        printf("*");
    }
}
int main(){
    int n;
    printf("entrez la valeur que vous voulez pour afficher un carré de * : ");
    while(scanf("%d",&n) != 1){
        printf("entrez une valeur valide \n");
        printf("entrez la valeur que vous voulez pour afficher un carré de * : ");
        while(getchar()!='\n');
    }
    for(int i=0;i<n;i++){
        ligne_etoile(n);
        printf("\n");
    }
}