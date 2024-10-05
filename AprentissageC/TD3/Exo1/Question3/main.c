#include <stdio.h>
#define TAB_MAX 20

int main(){
    int tab[TAB_MAX],valeur,valPlusPetites = 0 ;
    for (int i = 0; i < TAB_MAX; i++)
    {
        printf("entrez la valeur de la case %d : ", i+1);
        while (scanf("%d",&tab[i]) != 1)
        {
            printf("entrez une valeur valide \n");
            printf("entrez la valeur de la case %d : ", i+1);
            while(getchar() != '\n');
        }
        
    }
    printf("entrez la valeur que vous souhaitez : ");
            while (scanf("%d",valeur) != 1)
        {
            printf("entrez une valeur valide \n");
            printf("entrez la valeur que vous souhaitez : ");
            while(getchar() != '\n');
        }
    for (int i = 0; i < TAB_MAX; i++)
    {
        if(tab[i]< valeur) valPlusPetites;
        
    }
    printf("le nombre de valeur plus petites que %d est  : %d",valeur,valPlusPetites)
    
}