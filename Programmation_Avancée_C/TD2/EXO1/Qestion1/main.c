#include <stdio.h>

int main(){
    int n,somme;

    printf("Entrez la valeur de votre factorielle : ");
    while (scanf("%d",&n) != 1)
    {
        printf("Erreur entrez une valeur valid \n");
        printf("Entrez la valeur de votre factorielle : ");
        while (getchar() != '\n');
        
    }
    somme = 1;
 //   for (int i = n; i > 0; i--)
    for (unsigned int i = n; i > 0; i--)
    {
        somme *= i;
    }
    printf("la valeur du factoriel est de : %d\n",somme);
    somme = 1 ;
    int i=n;
    while (i>0)
    {
        somme*= i;
        i--;
    }
    printf("la valeur du factoriel est de : %d\n",somme);

    return 0;
}