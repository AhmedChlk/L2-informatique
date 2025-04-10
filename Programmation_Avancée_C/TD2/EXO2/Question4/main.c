#include <stdio.h>

int main(){
    int n ,somme = 0;
    printf("Entrez votre nombre  : ");
    while (scanf("%d",&n) != 1)
    {
        printf("Erreur entrez une valeur valid \n");
        printf("Entrez votre nombre : ");
        while (getchar() != '\n');
        
    }
    for (int i = 1; i <= n; i++){
        somme = 0;
        for(int j=1;j<i;j++){
            if (i%j == 0)
            {
                somme += j;
            }
            
        }
        if(somme == i){
            printf("%d , ",i);
        }
    }
    
    
    return 0;
}