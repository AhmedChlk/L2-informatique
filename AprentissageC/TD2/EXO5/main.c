#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int main(){
    int n,nombre,nbcoup,trouve = 0,essaie,i=0;
    srand(time(NULL));
    printf("entrez la valeur maximal a deviner aleatoirement : ");
    while (scanf("%d",&n) != 1)
        {
            printf("Erreur entrez une valeur valide \n");
            printf("entrez la valeur maximal a deviner aleatoirement : ");
            while(getchar() != '\n');
        }
    nombre = rand() % n + 1 ;
    printf("tirage de nombre de coup que vous avez pour trouver le nombre ");
    
    nbcoup = rand() % 20 + 1;
    printf("vous avez %d coup pour trouver le nombre \n",nbcoup);
    while (i < nbcoup && trouve == 0 )
        {
            printf("entrez le %d essaie : ",i+1);
            while (scanf("%d",&essaie) != 1)
            {
                printf("Erreur entrez une valeur valide \n");
                printf("entrez le %d essaie : ",nbcoup+1);
                while(getchar() != '\n');
            }
            if(essaie == nombre){
                trouve = 1;
                printf("bravo vous avez trouvé le nombre qui est %d ", nombre);
            }
            else if(essaie > nombre) {
                printf("FAUX ,C\'est moins \n");
            }
            else{
                printf("FAUX ,C\'est plus \n");
            }
            i++;


        }
        if (trouve == 0)
        {
            printf("ayy tu as perdue tu devais deviner %d \n",nombre);
        }
        printf("%d",nombre);
        

    return 0;

}