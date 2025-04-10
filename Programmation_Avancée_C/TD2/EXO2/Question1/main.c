#include <stdio.h>

int main(){
    int n , premier = 1;
    printf("Entrez votre nombre  : ");
    while (scanf("%d",&n) != 1)
    {
        printf("Erreur entrez une valeur valid \n");
        printf("Entrez votre nombre : ");
        while (getchar() != '\n');
        
        
    }
    int number;
    printf("entrez nombre");
    while (getchar() != '\n');
    scanf("%d",&number);
    printf("%c",getchar());
    for (int i = 2; i < n; i++)
    {
        if(n % i == 0){
            printf("ce nombre n'est pas premier\n");
            premier = 0 ;
            break;
        }
    }
    if (premier == 1) {
        printf("ce nombre est premier \n");
    }
    
    

}