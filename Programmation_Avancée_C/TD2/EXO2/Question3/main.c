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
    for (int i = 1; i < n; i++)
    {
        if (n%i == 0){
            somme += i;
        }
    
    }
    (n == somme) ? printf("il est parfait") : printf("il n'est pas parfait"); 
    
    return 0;
}