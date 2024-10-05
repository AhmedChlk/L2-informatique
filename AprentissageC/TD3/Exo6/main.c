#include<stdio.h>
#define TAILLE_MATRICE 2
int main (){
    int mat1[TAILLE_MATRICE][TAILLE_MATRICE],mat2[TAILLE_MATRICE][TAILLE_MATRICE],produitMat[TAILLE_MATRICE][TAILLE_MATRICE];
    printf("remplissage de la matrice 1: \n");
    for(int i=0;i<TAILLE_MATRICE;i++){
        for(int j=0;j<TAILLE_MATRICE;j++){
            printf("entrez la valeur de mat1[%d][%d] : ",i+1,j+1);
            while(scanf("%d",&mat1[i][j]) != 1 ){
                printf("erreur entrez une valeur valid\n");
                printf("entrez la valeur de mat1[%d][%d] : ",i+1,j+1);
            }
        }
    }
    printf("remplissage de la matrice 2: \n");
        for(int i=0;i<TAILLE_MATRICE;i++){
            for(int j=0;j<TAILLE_MATRICE;j++){
                printf("entrez la valeur de mat2[%d][%d] : ",i+1,j+1);
                while(scanf("%d",&mat2[i][j]) != 1 ){
                    printf("erreur entrez une valeur valid\n");
                    printf("entrez la valeur de mat2[%d][%d] : ",i+1,j+1);
                }
            }
        }
    for (int i=0; i<TAILLE_MATRICE ;i++){
        for(int j=0;j<TAILLE_MATRICE;j++){
            produitMat[i][j] = 0;
            for (int k = 0; k < TAILLE_MATRICE; k++) { 
            produitMat[i][j] += mat1[i][k] * mat2[k][j];
        }
        }
    }

    for (int i=0; i<TAILLE_MATRICE ;i++){
        for(int j=0;j<TAILLE_MATRICE;j++){
           printf("ProduitMat[%d][%d] = %d\n",i,j,produitMat[i][j]);
        }
    }
}

