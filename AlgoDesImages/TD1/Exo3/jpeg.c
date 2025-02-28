#include <math.h>
#include <stdio.h>
#include "jpeg.h"


void pgm_extract_blk(pgm_t* inpgm, double bloc[N][N],int i,int j){
    for(int k=0;k<N;k++){
        for(int l=0;l<N;l++){
            bloc[k][l] = (double) inpgm->pixels[i+k][j+l];
        }
    }
}

void pgm_dct(double bloc[N][N]) {
    double DCT[N][N];  // Matrice pour stocker le résultat de la DCT
    double Ci, Cj, somme;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            // Détermination des coefficients de normalisation
            Ci = (i == 0) ? 1.0 / sqrt(2) : 1.0;
            Cj = (j == 0) ? 1.0 / sqrt(2) : 1.0;

            somme = 0.0;
            for (int x = 0; x < N; x++) {
                for (int y = 0; y < N; y++) {
                    somme += bloc[x][y] * 
                             cos(((2 * x + 1) * i * M_PI) / (2.0 * N)) * 
                             cos(((2 * y + 1) * j * M_PI) / (2.0 * N));
                }
            }
            // Applique le facteur de normalisation et le coefficient
            DCT[i][j] = (2.0 / N) * Ci * Cj * somme;
        }
    }

    // Copie le résultat dans le bloc d'entrée
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            bloc[i][j] = DCT[i][j];
        }
    }
}


void pgm_quantify(double bloc[N][N], int Q[N][N]){
    int DCT[N][N];
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            DCT[i][j] = round(bloc[i][j] / Q[i][j]);
        }

    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            bloc[i][j] = DCT[i][j];
        }
    }
}

void pgm_zigzag(double bloc[N][N], double zigzag[N*N]) {
    int row = 0, col = 0;
    
    for (int k = 0; k < N * N; k++) {
        zigzag[k] = bloc[row][col];
        if ((row + col) % 2 == 0) { 
            if (col == N - 1) { 
                row++; 
            } else if (row == 0) { 
                col++;  
            } else { 
                row--; col++; 
            }
        } else {  
            if (row == N - 1) { 
                col++;  
            } else if (col == 0) { 
                row++;  
            } else { 
                row++; col--;  
            }
        }
    }
}

void pgm_rle(FILE *fd, double zgzg[N*N]){
    int i = 0;
    
    while (i < N*N) {
        int count = 1;
        
        while ((i + count < N*N) && (zgzg[i] == zgzg[i + count])) {
            count++;
        }

        if (count >= 2) {
            fprintf(fd, "@$%d$\n", count);
        }
        fprintf(fd, "%lf\n", zgzg[i]);

        i += count;
    }
}

void pgm_to_jpeg(pgm_t *in_pgm,char *fname){
    
}
