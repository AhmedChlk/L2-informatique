#include <stdio.h>

//#define TAILLE_MATRICE 2
const int TAILLE_MATRICE=2;

void MultMat(int mat1[TAILLE_MATRICE][TAILLE_MATRICE] ,int mat2[TAILLE_MATRICE][TAILLE_MATRICE] ,int F[TAILLE_MATRICE][TAILLE_MATRICE] ){
    
    for (int i=0; i<TAILLE_MATRICE ;i++){
        for(int j=0;j<TAILLE_MATRICE;j++){
            F[i][j] = 0;
            for (int k = 0; k < TAILLE_MATRICE; k++) { 
            F[i][j] += mat1[i][k] * mat2[k][j];
            }   
        }
    }
}

int main(){
    int n;
    int F[2][2]={{1,1},{1,0}};
    int R[TAILLE_MATRICE][TAILLE_MATRICE];
    printf("entrez le nombre que vous souhaitez pour le fibo : ");
    //lecture nombre fibo
    while(scanf("%d",&n) != 1 && n >= 0){
        printf("erreur entrez une valeur valide. \n");
        printf("entrez le nombre que vous souhaitez pour le fibo : ");
        while(getchar() != '\n');
    }
    if(n==0){
        printf("le resultat est : %d ",F[1][1]);
    }
    else if ( n== 1){
        printf("le resultat est : %d" ,F[0][1]);
    }
    else{
        for (int i = 2; i<n;i++){
            MultMat(F,F,R);
            for(int j=0 ;j<TAILLE_MATRICE;j++){
                for (int k=0;k<TAILLE_MATRICE;k++){
                    F[j][k] = R[j][k];
                }
            }
        }
        printf("le resultat est : %d\n" ,R[0][0]);
    }
    return 0;
}