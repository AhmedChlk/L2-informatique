#include <stdio.h>

#define SIZE 2

void MultMat(int mat1[SIZE][SIZE], int mat2[SIZE][SIZE], int F[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            F[i][j] = 0;
            for (int k = 0; k < SIZE; k++) {
                F[i][j] += mat1[i][k] * mat2[k][j];
            }
        }
    }
}

void MatrixPower(int F[SIZE][SIZE], int n) {
    int R[SIZE][SIZE] = {{0, 0}, {0, 0}};
    //int M[SIZE][SIZE] = {{1, 1}, {1, 0}};
    //copie F dans M
       for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            M[i][j] = F[i][j];
        }
    }
    for (int i = 1; i < n-1; i++) {
        MultMat(F, M, R);
        for(int j = 0;j<SIZE;j++){
            for(int k=0;k<SIZE;k++){
                F[j][k] = R[j][k];
            }
        }
    }
}

int main() {
    int n;
    int F[SIZE][SIZE] = {{1, 1}, {1, 0}};

    printf("Entrez le nombre que vous souhaitez pour le fibo : ");
    while (scanf("%d", &n) != 1 || n < 0) {
        printf("Erreur, entrez une valeur valide. \n");
        printf("Entrez le nombre que vous souhaitez pour le fibo : ");
        while (getchar() != '\n');
    }

    if (n == 0) {
        printf("Le resultat est : 0\n");
    } else if (n == 1) {
        printf("Le resultat est : 1\n");
    } else {
        MatrixPower(F, n);
        printf("Le resultat est : %d\n", F[0][0]);
    }
    
    return 0;
}
