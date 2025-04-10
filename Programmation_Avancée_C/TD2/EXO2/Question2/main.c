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
    for (int i = 1; i <= n; i++)
    {
        premier = 1;
        for (int j=2 ;j<i;j++)
        {
            if(i%j == 0){
                premier = 0;

            }
        }
        if (premier == 1){
            printf("%d , ",i);
        }
        
    
    }
    
    return 0;
}