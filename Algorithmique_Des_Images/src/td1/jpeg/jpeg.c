#include "jpeg.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ------------------------------------------------------------------------- 
   Fonctions de compression JPEG 
   ------------------------------------------------------------------------- */

/**
 * Extrait un bloc 8x8 d'une image PGM.
 * @param in_pgm Pointeur sur l'image PGM source.
 * @param bloc   Matrice 8x8 (double) qui recevra les valeurs du bloc extrait.
 * @param i      Indice de ligne (début du bloc dans l'image).
 * @param j      Indice de colonne (début du bloc dans l'image).
 */
void pgm_extract_blk(const pgm_t* in_pgm, double bloc[N][N], int i, int j) {
    for (int k = 0; k < N; k++) {
        for (int l = 0; l < N; l++) {
            bloc[k][l] = (double) in_pgm->pixels[i + k][j + l];
        }
    }
}

/**
 * Applique la DCT (Discrete Cosine Transform) sur un bloc 8x8.
 * Le bloc fourni est transformé en place.
 * @param bloc Matrice 8x8 de valeurs (entrées et sorties).
 */
void pgm_dct(double bloc[N][N]) {
    double DCT[N][N];
    for (int u = 0; u < N; u++) {
        for (int v = 0; v < N; v++) {
            double Cu = (u == 0) ? 1.0 / sqrt(2.0) : 1.0;
            double Cv = (v == 0) ? 1.0 / sqrt(2.0) : 1.0;
            double somme = 0.0;
            for (int x = 0; x < N; x++) {
                for (int y = 0; y < N; y++) {
                    somme += bloc[x][y] 
                             * cos(((2 * x + 1) * u * M_PI) / (2.0 * N))
                             * cos(((2 * y + 1) * v * M_PI) / (2.0 * N));
                }
            }
            DCT[u][v] = 0.25 * Cu * Cv * somme; // 0.25 = 2/N depuis N=8 (2/8 = 0.25)
        }
    }
    // Recopie du résultat dans le bloc
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            bloc[i][j] = DCT[i][j];
        }
    }
}

/**
 * Quantifie (réduit la précision) d'un bloc DCT 8x8 en utilisant une matrice de quantification.
 * @param bloc Matrice 8x8 contenant les coefficients DCT (modifiée en sortie).
 * @param Q    Matrice 8x8 des pas de quantification à utiliser.
 */
void pgm_quantify(double bloc[N][N], const int Q[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            // On arrondit le résultat de la division par le pas de quantification
            bloc[i][j] = round(bloc[i][j] / Q[i][j]);
        }
    }
}

/**
 * Parcours en zigzag d'un bloc 8x8 pour produire un vecteur de 64 coefficients.
 * @param bloc   Matrice 8x8 de coefficients (typiquement DCT quantifiés).
 * @param zigzag Tableau de 64 entiers qui recevra le résultat du parcours zigzag.
 */
void pgm_zigzag(const double bloc[N][N], int zigzag[N * N]) {
    int index = 0;
    int row = 0, col = 0;
    for (int k = 0; k < N * N; k++) {
        zigzag[k] = (int) bloc[row][col];
        // Déplacement dans le parcours zigzag
        if ((row + col) % 2 == 0) { // Diagonale montante
            if (col == N - 1) {
                row++;
            } else if (row == 0) {
                col++;
            } else {
                row--;
                col++;
            }
        } else { // Diagonale descendante
            if (row == N - 1) {
                col++;
            } else if (col == 0) {
                row++;
            } else {
                row++;
                col--;
            }
        }
    }
}

/**
 * Compression RLE (Run-Length Encoding) d'un bloc zigzag.
 * Écrit le résultat dans un fichier ouvert.
 * @param f    Pointeur de fichier ouvert en écriture.
 * @param zigzag Tableau de 64 entiers représentant les coefficients en zigzag.
 */
void pgm_rle(FILE* f, const int zigzag[N * N]) {
    int k = 0;
    while (k < N * N) {
        if (zigzag[k] == 0) {
            // Compter les zéros consécutifs
            int count = 1;
            while (k + count < N * N && zigzag[k + count] == 0) {
                count++;
            }
            if (count >= 2) {
                fprintf(f, "@%d\n", count);
            } else {
                fprintf(f, "%d\n", zigzag[k]);
            }
            k += count;
        } else {
            fprintf(f, "%d\n", zigzag[k]);
            k++;
        }
    }
}

/**
 * Fonction principale de compression JPEG d'une image PGM.
 * Divise l'image en blocs 8x8, applique la DCT, la quantification et le RLE, 
 * puis écrit le résultat dans un fichier texte.
 * @param in_pgm Pointeur sur l'image PGM à compresser.
 * @param fname  Nom du fichier de sortie (format texte JPEG simulé).
 */
void pgm_to_jpeg(const pgm_t* in_pgm, const char* fname) {
    // Matrice de quantification standard (exemple)
    const int Q[N][N] = {
        {16, 11, 10, 16, 24, 40, 51, 61},
        {12, 12, 14, 19, 26, 58, 60, 55},
        {14, 13, 16, 24, 40, 57, 69, 56},
        {14, 17, 22, 29, 51, 87, 80, 62},
        {18, 22, 37, 56, 68, 109, 103, 77},
        {24, 35, 55, 64, 81, 104, 113, 92},
        {49, 64, 78, 87, 103, 121, 120, 101},
        {72, 92, 95, 98, 112, 100, 103, 99}
    };
    FILE* f = fopen(fname, "w");
    if (f == NULL) {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier %s en écriture.\n", fname);
        return;
    }
    // Écriture de l'en-tête du fichier compressé
    fprintf(f, "JPEG\n");
    fprintf(f, "%d %d\n", in_pgm->width, in_pgm->height);
    // Traiter l'image par blocs de 8x8
    for (int i = 0; i + N <= in_pgm->height; i += N) {
        for (int j = 0; j + N <= in_pgm->width; j += N) {
            double bloc[N][N];
            pgm_extract_blk(in_pgm, bloc, i, j);
            pgm_dct(bloc);
            pgm_quantify(bloc, Q);
            int zigzag[N * N];
            pgm_zigzag(bloc, zigzag);
            pgm_rle(f, zigzag);
        }
    }
    fclose(f);
}

/**
 * Retourne la taille d'un fichier en octets.
 * @param fname Nom du fichier.
 * @return Taille du fichier en octets, ou -1 en cas d'erreur.
 */
int taille_fichier(const char* fname) {
    FILE* f = fopen(fname, "rb");
    if (f == NULL) {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier %s.\n", fname);
        return -1;
    }
    fseek(f, 0L, SEEK_END);
    long size = ftell(f);
    fclose(f);
    return (int) size;
}

/* ------------------------------------------------------------------------- 
   Fonctions de décompression JPEG 
   ------------------------------------------------------------------------- */

/**
 * Parcours zigzag inverse pour reconstruire un bloc 8x8 à partir de 64 coefficients.
 * @param zigzag Tableau de 64 entiers (coefficients en zigzag).
 * @param bloc   Matrice 8x8 (double) à remplir avec les coefficients aux bonnes positions.
 */
void inverse_zigzag(const int zigzag[N * N], double bloc[N][N]) {
    // Tableau pour stocker les coordonnées de chaque position zigzag
    int coords[N * N][2];
    int row = 0, col = 0;
    for (int k = 0; k < N * N; k++) {
        coords[k][0] = row;
        coords[k][1] = col;
        if ((row + col) % 2 == 0) { // Diagonale montante
            if (col == N - 1) {
                row++;
            } else if (row == 0) {
                col++;
            } else {
                row--;
                col++;
            }
        } else { // Diagonale descendante
            if (row == N - 1) {
                col++;
            } else if (col == 0) {
                row++;
            } else {
                row++;
                col--;
            }
        }
    }
    // Placement des valeurs depuis le tableau zigzag vers le bloc 2D
    for (int k = 0; k < N * N; k++) {
        int r = coords[k][0];
        int c = coords[k][1];
        bloc[r][c] = zigzag[k];
    }
}

/**
 * Applique l'inverse de la DCT (IDCT) sur un bloc 8x8.
 * Le bloc est modifié en place et redevient des valeurs de pixels (0-255 normalement).
 * @param bloc Matrice 8x8 de coefficients (généralement déquantifiés) à transformer.
 */
void pgm_idct(double bloc[N][N]) {
    double temp[N][N];
    for (int x = 0; x < N; x++) {
        for (int y = 0; y < N; y++) {
            double somme = 0.0;
            for (int u = 0; u < N; u++) {
                for (int v = 0; v < N; v++) {
                    double Cu = (u == 0) ? 1.0 / sqrt(2.0) : 1.0;
                    double Cv = (v == 0) ? 1.0 / sqrt(2.0) : 1.0;
                    somme += Cu * Cv * bloc[u][v]
                             * cos(((2 * x + 1) * u * M_PI) / (2.0 * N))
                             * cos(((2 * y + 1) * v * M_PI) / (2.0 * N));
                }
            }
            temp[x][y] = 0.25 * somme;
        }
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            bloc[i][j] = temp[i][j];
        }
    }
}

/**
 * Fonction principale de décompression JPEG.
 * Lit un fichier compressé (texte) créé par pgm_to_jpeg et reconstruit une image PGM.
 * @param fname Nom du fichier JPEG (texte) à lire.
 * @return Pointeur sur l'image PGM reconstruite, ou NULL en cas d'erreur.
 */
pgm_t* jpeg_to_pgm(const char* fname) {
    FILE* f = fopen(fname, "r");
    if (f == NULL) {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier %s.\n", fname);
        return NULL;
    }
    char header[10];
    if (fscanf(f, "%9s", header) != 1 || strcmp(header, "JPEG") != 0) {
        fprintf(stderr, "Format de fichier inconnu ou invalide.\n");
        fclose(f);
        return NULL;
    }
    int width = 0, height = 0;
    if (fscanf(f, "%d %d", &width, &height) != 2) {
        fprintf(stderr, "Dimensions manquantes dans le fichier JPEG.\n");
        fclose(f);
        return NULL;
    }
    pgm_t* img = pgm_alloc(height, width, 255);
    if (img == NULL) {
        fclose(f);
        return NULL;
    }
    // Même matrice de quantification que lors de la compression
    const int Q[8][8] = {
        {16, 11, 10, 16, 24, 40, 51, 61},
        {12, 12, 14, 19, 26, 58, 60, 55},
        {14, 13, 16, 24, 40, 57, 69, 56},
        {14, 17, 22, 29, 51, 87, 80, 62},
        {18, 22, 37, 56, 68, 109, 103, 77},
        {24, 35, 55, 64, 81, 104, 113, 92},
        {49, 64, 78, 87, 103, 121, 120, 101},
        {72, 92, 95, 98, 112, 100, 103, 99}
    };
    // Traitement bloc par bloc
    for (int i = 0; i < height; i += N) {
        for (int j = 0; j < width; j += N) {
            // Lecture des 64 coefficients en zigzag (avec RLE)
            int zigzag[N * N];
            int index = 0;
            while (index < N * N) {
                char token[20];
                if (fscanf(f, "%19s", token) != 1) break;
                if (token[0] == '@') {
                    int count = atoi(token + 1);
                    for (int k = 0; k < count && index < N * N; k++) {
                        zigzag[index++] = 0;
                    }
                } else {
                    zigzag[index++] = atoi(token);
                }
            }
            double bloc[N][N];
            inverse_zigzag(zigzag, bloc);
            // Déquantification: multiplie chaque coefficient par le pas de quantification
            for (int x = 0; x < N; x++) {
                for (int y = 0; y < N; y++) {
                    bloc[x][y] *= Q[x][y];
                }
            }
            pgm_idct(bloc);
            // Réinjecte le bloc reconstruit dans l'image
            for (int x = 0; x < N; x++) {
                for (int y = 0; y < N; y++) {
                    int pixel = (int) round(bloc[x][y]);
                    if (pixel < 0) pixel = 0;
                    if (pixel > 255) pixel = 255;
                    img->pixels[i + x][j + y] = (unsigned char) pixel;
                }
            }
        }
    }
    fclose(f);
    return img;
}
