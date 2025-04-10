#include <stdio.h>

int main(){
    int n ,i=2;
    printf("Entrez votre nombre  : ");
    while (scanf("%d",&n) != 1)
    {
        printf("Erreur entrez une valeur valid \n");
        printf("Entrez votre nombre : ");
        while (getchar() != '\n');
        
    }
    while (i<n && n%i != 0)
    {
        i++;
    }
    if (i == n) {
        printf("ce nombre est premier \n");
    }else{
        printf("ce nombre n\'est pas premier \n");
    }
    
    return 0;
    

}