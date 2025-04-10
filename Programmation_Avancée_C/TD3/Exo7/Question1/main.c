#include <stdio.h>
int fibonacci (int n){
    if(n == 1 ) return 1;
    else if(n == 0 ) return 0 ;
    else return fibonacci(n-1) + fibonacci(n-2);
}

int main(){
    int n,resultat,termeN_1=0,termeN=1,termeNplus;
    printf("entrez le nombre que vous souhaitez pour le fibo : ");
    while(scanf("%d",&n) != 1 && n >= 0){
        printf("erreur entrez une valeur valide. \n");
        printf("entrez le nombre que vous souhaitez pour le fibo : ");
        while(getchar() != '\n');
    }
    if(n==  0)
        printf("le resultat est 0 ");
    else if ( n == 1 )
        printf("le resultat est 1 ");
    else{   
        for(int i=2;i<=n;i++){
            termeNplus = termeN + termeN_1 ;
            termeN_1 = termeN;
            termeN = termeNplus;
        }
        printf("le resultat est : %d\n",termeN);
    }
    resultat = fibonacci(n);
    printf("le resultat en recurssif : %d\n", resultat);
    return 0;
}