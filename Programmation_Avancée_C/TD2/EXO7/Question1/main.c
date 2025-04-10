#include <stdio.h>

int main(){
    int a,n,un;
    printf("entrez la valeur de a : ");
    while (scanf("%d",&a) != 1)
        {
            printf("Erreur entrez une valeur valide \n");
            printf("entrez la valeur de a : ");
            while(getchar() != '\n');
        }
    printf("entrez la valeur de n : ");
    while (scanf("%d",&n) != 1)
        {
            printf("Erreur entrez une valeur valide \n");
            printf("entrez la valeur de n : ");
            while(getchar() != '\n');
        }
    un = a;
    for (int i = 1; i < n; i++)
    {
        if (un % 2 == 0 ) un /= 2;
        else un = 3*un + 1;
        printf("U%d = %d \n",i,un);
    }
    

    return 0;
    
}