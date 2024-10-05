#include <stdio.h>

int main(){
    int l,longueurSuite=0,un,longueurSuiteMax=0,a;
    printf("entrez la valeur de l : ");
    while (scanf("%d",&l) != 1)
        {
            printf("Erreur entrez une valeur valide \n");
            printf("entrez la valeur de a : ");
            while(getchar() != '\n');
            
        }
    for(int i=2;i<=l;i++){
        longueurSuite = 0 ;
        un = i ;
        
        while(un != 1){
            longueurSuite ++;
            if (un % 2 == 0 ) un /= 2;
            else un = 3*un + 1;
        }
        printf("la longueur de la suite est de : %d avec a = %d \n",longueurSuite,i);
        if(longueurSuite > longueurSuiteMax){
            a = i;
            longueurSuiteMax = longueurSuite;
        }

    }

    printf("la valeur de a comprise entre 2 et l qui maximise le k est de : %d avec un k de : %d",a,longueurSuiteMax);
    return 0;
    
}