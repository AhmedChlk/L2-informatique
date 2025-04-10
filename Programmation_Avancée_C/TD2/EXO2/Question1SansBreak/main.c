#include <stdio.h>

int main(){
    int n , premier = 1,i=2;
    printf("Entrez votre nombre  : ");
    while (scanf("%d",&n) != 1)
    {
        printf("Erreur entrez une valeur valid \n");
        printf("Entrez votre nombre : ");
        while (getchar() != '\n');
        
    }
    while (i<n && premier == 1)
    {
        if(n % i == 0){
            printf("ce nombre n'est pas premier\n");
            premier = 0 ;
        }
        i++;
    }
    if (premier == 1) {
        printf("ce nombre est premier \n");
    }
    
    return 0;
    

}