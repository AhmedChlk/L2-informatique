#include<stdio.h>

int main(){
    int a,b,r=0;
    printf("entrez la valeur de a : ");
    while (scanf("%d",&a) != 1)
        {
            printf("Erreur entrez une valeur valide \n");
            printf("entrez la valeur de a : ");
            while(getchar() != '\n');
        }
    printf("entrez la valeur de b : ");
    while (scanf("%d",&b) != 1)
        {
            printf("Erreur entrez une valeur valide \n");
            printf("entrez la valeur de b : ");
            while(getchar() != '\n');
        }
    printf("%d x %d = ",a,b);
    while (b != 0)
    {
        if(b%2 == 0){
            a*=2;
            b/=2;
        }else{
            r += a;
            b--;

        }
    }
    printf("%d\n",r);
    return 0;
    
}