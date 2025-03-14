#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jpeg.h"

// Extraction d'un bloc 8x8 d'une image PGM
void pgm_extract_blk(pgm_t* inpgm, double bloc[N][N], int i, int j) {
    for (int k = 0; k < N; k++) {
        for (int l = 0; l < N; l++) {
            bloc[k][l] = (double) inpgm->pixels[i + k][j + l];
        }
    }
}

// Application de la DCT sur un bloc 8x8
void pgm_dct(double bloc[N][N]) {
    double DCT[N][N];
    double Ci, Cj, somme;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
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
            DCT[i][j] = (2.0 / N) * Ci * Cj * somme;
        }
    }
    // Recopie du résultat dans le bloc
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            bloc[i][j] = DCT[i][j];
}

// Quantification d'un bloc 8x8
void pgm_quantify(double bloc[N][N], int Q[N][N]) {
    int temp[N][N];
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            temp[i][j] = round(bloc[i][j] / Q[i][j]);
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            bloc[i][j] = temp[i][j];
}

// Parcours en zigzag d'un bloc 8x8
void pgm_zigzag(double bloc[N][N], int zigzag[N * N]) {
    int row = 0, col = 0;
    for (int k = 0; k < N * N; k++) {
        zigzag[k] = (int) bloc[row][col];
        if ((row + col) % 2 == 0) { // diagonale montante
            if (col == N - 1)
                row++;
            else if (row == 0)
                col++;
            else {
                row--;
                col++;
            }
        } else { // diagonale descendante
            if (row == N - 1)
                col++;
            else if (col == 0)
                row++;
            else {
                row++;
                col--;
            }
        }
    }
}

// Compression RLE d'un bloc zigzag
void pgm_rle(FILE *fd, int zgzg[N * N]) {
    int i = 0;
    while (i < N * N) {
        if (zgzg[i] == 0) {
            int count = 1;
            while ((i + count < N * N) && (zgzg[i] == zgzg[i + count]))
                count++;
            if (count >= 2)
                fprintf(fd, "@%d\n", count);
            else
                fprintf(fd, "%d\n", zgzg[i]);
            i += count;
        } else {
            fprintf(fd, "%d\n", zgzg[i]);
            i++;
        }
    }
}

// Fonction principale de compression JPEG
void pgm_to_jpeg(pgm_t *in_pgm, char *fname) {
    int Q[N][N] = {
        {16, 11, 10, 16, 24, 40, 51, 61},
        {12, 12, 14, 19, 26, 58, 60, 55},
        {14, 13, 16, 24, 40, 57, 69, 56},
        {14, 17, 22, 29, 51, 87, 80, 62},
        {18, 22, 37, 56, 68, 109, 103, 77},
        {24, 35, 55, 64, 81, 104, 113, 92},
        {49, 64, 78, 87, 103, 121, 120, 101},
        {72, 92, 95, 98, 112, 100, 103, 99}
    };
    FILE *F = fopen(fname, "w");
    if (F == NULL) {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier %s\n", fname);
        return;
    }
    fprintf(F, "JPEG\n");
    fprintf(F, "%d %d\n", in_pgm->width, in_pgm->height);
    for (int i = 0; i + N <= in_pgm->height; i += N) {
        for (int j = 0; j + N <= in_pgm->width; j += N) {
            double bloc[N][N];
            pgm_extract_blk(in_pgm, bloc, i, j);
            pgm_dct(bloc);
            pgm_quantify(bloc, Q);
            int zigzag[N * N];
            pgm_zigzag(bloc, zigzag);
            pgm_rle(F, zigzag);
        }
    }
    fclose(F);
}

// Retourne la taille d'un fichier en octets
int fsize(char *fname) {
    FILE *F = fopen(fname, "r");
    if (F == NULL) {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier %s\n", fname);
        return -1;
    }
    fseek(F, 0L, SEEK_END);
    int size = ftell(F);
    fclose(F);
    return size;
}

// Fonction inverse du parcours zigzag pour reconstruire un bloc 8x8
void inverse_zigzag(int zigzag[N * N], double bloc[N][N]) {
    int coords[N * N][2];
    int row = 0, col = 0;
    for (int k = 0; k < N * N; k++) {
        coords[k][0] = row;
        coords[k][1] = col;
        if ((row + col) % 2 == 0) { // diagonale montante
            if (col == N - 1)
                row++;
            else if (row == 0)
                col++;
            else {
                row--;
                col++;
            }
        } else { // diagonale descendante
            if (row == N - 1)
                col++;
            else if (col == 0)
                row++;
            else {
                row++;
                col--;
            }
        }
    }
    for (int k = 0; k < N * N; k++) {
        int r = coords[k][0];
        int c = coords[k][1];
        bloc[r][c] = zigzag[k];
    }
}

// Application de l'inverse de la DCT (IDCT) sur un bloc 8x8
void pgm_idct(double bloc[N][N]) {
    double temp[N][N];
    for (int x = 0; x < N; x++) {
        for (int y = 0; y < N; y++) {
            double sum = 0.0;
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < N; j++) {
                    double Ci = (i == 0) ? 1.0 / sqrt(2) : 1.0;
                    double Cj = (j == 0) ? 1.0 / sqrt(2) : 1.0;
                    sum += Ci * Cj * bloc[i][j] *
                           cos(((2 * x + 1) * i * M_PI) / (2.0 * N)) *
                           cos(((2 * y + 1) * j * M_PI) / (2.0 * N));
                }
            }
            temp[x][y] = (2.0 / N) * sum;
        }
    }
    for (int x = 0; x < N; x++)
        for (int y = 0; y < N; y++)
            bloc[x][y] = temp[x][y];
}

// Fonction principale de décompression JPEG
pgm_t* jpeg_to_pgm(char *fname) {
    FILE *F = fopen(fname, "r");
    if (F == NULL) {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier %s\n", fname);
        return NULL;
    }
    char header[10];
    fscanf(F, "%s", header);
    if (strcmp(header, "JPEG") != 0) {
        fprintf(stderr, "Format non reconnu\n");
        fclose(F);
        return NULL;
    }
    int width, height;
    fscanf(F, "%d %d", &width, &height);
    pgm_t *img = pgm_alloc(height, width, 255);
    int Q[8][8] = {
        {16, 11, 10, 16, 24, 40, 51, 61},
        {12, 12, 14, 19, 26, 58, 60, 55},
        {14, 13, 16, 24, 40, 57, 69, 56},
        {14, 17, 22, 29, 51, 87, 80, 62},
        {18, 22, 37, 56, 68, 109, 103, 77},
        {24, 35, 55, 64, 81, 104, 113, 92},
        {49, 64, 78, 87, 103, 121, 120, 101},
        {72, 92, 95, 98, 112, 100, 103, 99}
    };
    // Traitement par blocs
    for (int i = 0; i < height; i += N) {
        for (int j = 0; j < width; j += N) {
            int zigzag[N * N];
            int index = 0;
            // Décodage RLE pour obtenir 64 coefficients
            while (index < N * N) {
                char token[20];
                if (fscanf(F, "%s", token) != 1)
                    break;
                if (token[0] == '@') {
                    int count = atoi(token + 1);
                    for (int k = 0; k < count && index < N * N; k++)
                        zigzag[index++] = 0;
                } else {
                    zigzag[index++] = atoi(token);
                }
            }
            double bloc[N][N];
            inverse_zigzag(zigzag, bloc);
            // Déquantification
            for (int x = 0; x < N; x++)
                for (int y = 0; y < N; y++)
                    bloc[x][y] = bloc[x][y] * Q[x][y];
            // Application de l'IDCT
            pgm_idct(bloc);
            // Placement du bloc dans l'image
            for (int x = 0; x < N; x++) {
                for (int y = 0; y < N; y++) {
                    int pixel = round(bloc[x][y]);
                    if (pixel < 0) pixel = 0;
                    if (pixel > 255) pixel = 255;
                    img->pixels[i + x][j + y] = (unsigned char) pixel;
                }
            }
        }
    }
    fclose(F);
    return img;
}
