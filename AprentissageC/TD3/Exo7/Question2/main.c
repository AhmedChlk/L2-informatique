#include <stdio.h>

#define TAILLE_MATRICE 2

void MultMat(int mat1[TAILLE_MATRICE][TAILLE_MATRICE], int mat2[TAILLE_MATRICE][TAILLE_MATRICE], int F[TAILLE_MATRICE][TAILLE_MATRICE]) {
    for (int i = 0; i < TAILLE_MATRICE; i++) {
        for (int j = 0; j < TAILLE_MATRICE; j++) {
            F[i][j] = 0;
            for (int k = 0; k < TAILLE_MATRICE; k++) {
                F[i][j] += mat1[i][k] * mat2[k][j];
            }
        }
    }
}

void MatrixPower(int F[TAILLE_MATRICE][TAILLE_MATRICE], int n) {
    int R[TAILLE_MATRICE][TAILLE_MATRICE] = {{0, 0}, {0, 0}};
    int M[TAILLE_MATRICE][TAILLE_MATRICE] = {{1, 1}, {1, 0}};

    for (int i = 1; i < n-1; i++) {
        MultMat(F, M, R);
        for(int j = 0;j<TAILLE_MATRICE;j++){
            for(int k=0;k<TAILLE_MATRICE;k++){
                F[j][k] = R[j][k];
            }
        }
    }
}

int main() {
    int n;
    int F[TAILLE_MATRICE][TAILLE_MATRICE] = {{1, 1}, {1, 0}};

    printf("Entrez le nombre que vous souhaitez pour le fibo : ");
    while (scanf("%d", &n) != 1 || n < 0) {
        printf("Erreur, entrez une valeur valide. \n");
        printf("Entrez le nombre que vous souhaitez pour le fibo : ");
        while (getchar() != '\n');
    }

    if (n == 0) {
        printf("Le résultat est : 0\n");
    } else if (n == 1) {
        printf("Le résultat est : 1\n");
    } else {
        MatrixPower(F, n);
        printf("Le résultat est : %d\n", F[0][0]);
    }
    
    return 0;
}
