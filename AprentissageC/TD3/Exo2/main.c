#include<stdio.h>

int main(){

    int tab[10],e=0,permutation = 1,contenanceNombre;
    for (int i = 0; i < 10; i++){
        printf("entrez tab[%d] : ",i+1);
        while(scanf("%d",&tab[i])!= 1){
            printf("Entrez une valeur valide\n");
            printf("entrez tab[%d] : ",i+1);
            while(getchar() != '\n');
        }
    }
    while (e<10 && permutation == 1)
    {
        contenanceNombre = 0 ;
        for (int i =0 ; i < 10 ;i++){
            if(tab[i] == e) contenanceNombre = 1;
        }
        if (!contenanceNombre) permutation = 0;
        e++;
    }
    if(permutation){
        printf("c'est une permutation\n");
    }
    else{
        printf("ce n'est pas une permutation\n");
    }
    
    
}