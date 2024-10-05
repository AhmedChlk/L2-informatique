#include <stdio.h>
#include<stdlib.h>

int main(){
    int tailleTab,k,pas;
     
    printf("entrez la taille du tableau : ");
    while (scanf("%d",&tailleTab) != 1)
        {
            printf("entrez une valeur valide \n");
            printf("entrez la taille du tableau : ");
            while(getchar() != '\n');
        }

    printf("Entrez le pas de la rotation :"); 
        while (scanf("%d",&pas) != 1)
        {
        printf("entrez une valeur valide \n");
        printf("Entrez le pas de la rotation :"); 
            while(getchar() != '\n');
        }

    int tab[tailleTab], tabrotation[tailleTab];
    for (int i = 0; i < tailleTab; i++)
    {
        printf("entrez tab[%d] : ",i+1);
        while (scanf("%d",&tab[i]) != 1)
        {
            printf("entrez une valeur valide \n");
            printf("entrez tab[%d] : ",i+1);
            while(getchar() != '\n');
        }


    }

    for (int i = 0; i < tailleTab ; i++)
    {
        k = i + pas;
        if(k<tailleTab) tabrotation[k] = tab[i];
        else tabrotation[k-tailleTab] = tab[i]; 
    }

    for (int i = 0; i < tailleTab; i++)
    {
        printf("tab[%d] : %d\n ",i+1 , tab[i] );
    }
        for (int i = 0; i < tailleTab; i++)
    {
        printf("tabrotation[%d] : %d\n ",i+1 , tabrotation[i] );
    }
    
    
}