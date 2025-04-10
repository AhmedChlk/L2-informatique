#include <stdio.h>

int main(){
    int n,j;
    printf("Entrez votre nombre  : ");
    while (scanf("%d",&n) != 1)
    {
        printf("Erreur entrez une valeur valid \n");
        printf("Entrez votre nombre : ");
        while (getchar() != '\n');
        
    }
    printf("1  ,  ");
    for (int i = 2; i <= n; i++)
    {
        j=2;
        while (j<i && i%j != 0)
        {
            j++;
        }
        if (i == j){
            printf("%d  ,  ",i);
        }
        
    
    }
    printf("\n");
    return 0;
}