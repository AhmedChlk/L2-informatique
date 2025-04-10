#include<stdio.h>
#include<stdlib.h>

float** allouer_matrice(int n, int m){
    float** mat = (float**) malloc(n * sizeof(float*));
    for(int i=0;i<n;i++){
        mat[i] = (float*) malloc (m * sizeof(float));
    }
    for(int i = 0;i<n;i++){
        for(int j=0;j<m;j++){
            mat[i][j] = 0;
        }
    }
    return mat;
    
}

void allouer_matrice_sansret (int n , int m , float*** mat){
    *mat = (float**) malloc(n * sizeof(float*));
    for(int i=0;i<n;i++){
        (*mat)[i] = (float*) malloc (m * sizeof(float));
    }
    for(int i = 0;i<n;i++){
        for(int j=0;j<m;j++){
            (*mat)[i][j] = 0;
        }
    }
}

void afficher_mat (float** mat,int n, int m){
    for(int i=0 ; i<n;i++){
        for(int j=0;j<m;j++){
            printf("%f ",mat[i][j]);
        }
        printf("\n");
    }
    
}

void mult_mat(float** mat1,float** mat2 ,float*** mat3 ,int n , int m , int p){
    /* mat1(n,m)
       mat2(m,p)
       mat3(n,p)
    */
    allouer_matrice_sansret(n,p,mat3);
    for(int i=0;i<n;i++){
        for(int j=0;j<p;j++){
            for(int k=0;k<m;k++){
                (*mat3)[i][j] += mat1[i][k] * mat2[k][j];
            }
        }
    }
}
void transpose_mat(float*** mat , int* n , int* m){
    if(n==m){
        if (*n == *m) {
        for (int i = 0; i < *n; i++) {
            for (int j = i + 1; j < *m; j++) {
                float temp = (*mat)[i][j];
                (*mat)[i][j] = (*mat)[j][i];
                (*mat)[j][i] = temp;
                }
        }

        }
        else {
        float** nouvelle_matrice = (float**)malloc(*m * sizeof(float*));
        for (int i = 0; i < *m; i++) {
            nouvelle_matrice[i] = (float*)malloc(*n * sizeof(float));
        }

        for (int i = 0; i < *n; i++) {
            for (int j = 0; j < *m; j++) {
                nouvelle_matrice[j][i] = (*mat)[i][j];
            }
        }

        for (int i = 0; i < *n; i++) {
            free((*mat)[i]);
        }
        free(*mat);

        *mat = nouvelle_matrice;

        int temp = *n;
        *n = *m;
        *m = temp;
    }
    }
}
int main(){
    float **mat,**mat2,**mat3;
    allouer_matrice_sansret(2,2,&mat);
    mat[0][0] = 1;
    mat[0][1] = 2;
    mat[1][0] = 3;
    mat[1][1] = 4;
    allouer_matrice_sansret(2,1,&mat2);
    mat2[0][0] = 2;
    mat2[1][0] = 2;
    mult_mat(mat,mat2,&mat3,2,2,1);
    afficher_mat(mat3,2,1);

}