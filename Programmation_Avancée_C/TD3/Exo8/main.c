#include <stdio.h>
#include<string.h>

char compter_nombre_chiffres(int n){
    int occ=0;
    while(n != 0){
        occ++;
        n/=10;
    }
    //return (char)occ;
    return (char)(occ+'0');
    //return (strfromf(str,(float)occ,"%f"))[0];
}

int main(){
    int n;
    printf("entrez une valeur superieur a 0 : ");
    while(scanf("%d",&n) != 1  || n < 1){
        printf("erreur entrez une valeur correct .\n");
        printf("entrez une valeur superieur a 0 : ");
        while(getchar() != '\n');
    }
    int trianglePascal [n][n];
    for(int i=0;i<n;i++){
        trianglePascal[i][0] = 1;
        trianglePascal[i][i] = 1;
        for(int j=1;j<i;j++){
            trianglePascal[i][j] = trianglePascal[i-1][j-1] + trianglePascal[i-1][j];
        }
    }

    //printf("\n[DEBUG 001]\n");fflush(stdout);
    char taille_espace[2]="0",espacenbr[5]=" %";
    //printf("\n[DEBUG 002]\n");fflush(stdout);
    taille_espace[0] = compter_nombre_chiffres(trianglePascal[n-1][n/2]);
    //printf("\n[DEBUG 003]\n");fflush(stdout);
    strcat(strcat(espacenbr,taille_espace),"d");
    //printf("\n[DEBUG 004]\n");fflush(stdout);
    //printf("%s",espacenbr);
    //printf("\n[DEBUG 005]\n");fflush(stdout);
     
    for(int i=0;i<n;i++){
        for(int j =0;j<=i;j++){
            printf(espacenbr,trianglePascal[i][j]);
        }
        printf("\n");
    }
    return 0;
}