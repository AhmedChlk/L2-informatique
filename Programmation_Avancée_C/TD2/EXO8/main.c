#include <stdio.h>

int main(){
    int longueurSapin,nombreEspace,nombreChapeau = 1;

    printf("entrez la longueur du Sapin  : ");
    while (scanf("%d",&longueurSapin) != 1)
        {
            printf("Erreur entrez une valeur valide \n");
            printf("entrez la longueur du Sapin  : ");
            while(getchar() != '\n');
            
        }
    nombreEspace = longueurSapin;
    for (int i = 0; i < longueurSapin; i++)
    {
        for (int j = 0; j < nombreEspace; j++) printf(" ");
           
        for (int k = 0; i < nombreChapeau; k++)  printf("^");
        printf("\n");
        nombreEspace --;
        nombreChapeau+=2;
    }
    return 0;

}