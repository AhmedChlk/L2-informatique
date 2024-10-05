#include <stdio.h>
#define TAB_MAX 20

int main(){
    int tab[TAB_MAX],maxTab,minTab,maxIndice,minIndice;
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
    maxIndice = 1;
    minIndice = 1;
    maxTab = tab[0];
    minTab = tab[0];
    for (int i = 0; i < TAB_MAX; i++)
    {
        printf(" la valeur de la case %d : %d\n", i+1,tab[i]);
        if(maxTab < tab[i]) {
        maxTab = tab[i];
        maxIndice = i+1;    
        }
        if(minTab > tab[i])
        {
         minTab = tab[i];
         minIndice = i+1;
        }
    }
    printf("le max est : %d  avec l'indice %d \nla min est : %d avec l'indice %d \n", maxTab ,maxIndice,minTab,minIndice );
    
}