#include <stdio.h>
#define TAB_MAX 20

int main(){
    int tab[TAB_MAX];
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

    for (int i = 0; i < TAB_MAX; i++)
    {
        printf(" la valeur de la case %d : %d\n", i+1,tab[i]);
    }
    
    
}