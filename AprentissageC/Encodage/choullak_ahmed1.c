#include<stdio.h>


int main(){
    int n;
    printf("entrez la valeur de : ");
    while(scanf("%d",&n) != 1){
        printf("erreur entrez une valide \n");
        while(getchar() != '\n');
        printf("entrez la valeur de : ");

    }
    if(n > 0 ){
        for(int i=0;i<n;i++){
            printf("19 points\n");
        }
    }else
        printf("erreur \n");   
    return 0;
}