#include <stdio.h>

int main(){
    int n;
    printf("entrez une valeur superieur a 0 : ");
    while(scanf("%d",&n) != 1  || n < 1){
        printf("erreur entrez une valeur correct .\n");
        printf("entrez une valeur superieur a 0 : ");
        while(getchar() != '\n');
    }
    int trianglePascal [n][n] = {};
    for(int i=0;i<n;i++){
        trianglePascal[i][0] = 1;
        trianglePascal[i][i] = 1;
        for(int j=1;j<i;j++){
            trianglePascal[i][j] = trianglePascal[i-1][j-1] + trianglePascal[i-1][j];
        }
    }

    for(int i=0;i<n;i++){
        for(int j =0;j<=i;j++){
            printf("%2d ",trianglePascal[i][j]);
        }
        printf("\n");
    }
    return 0;
}