#ifndef JPEG_H
#define JPEG_H

#include <stdio.h>
#include "pgm.h"

#define N 8

// Fonctions de compression JPEG
void pgm_extract_blk(const pgm_t* in_pgm, double bloc[N][N], int i, int j);
void pgm_dct(double bloc[N][N]);
void pgm_quantify(double bloc[N][N], const int Q[N][N]);
void pgm_zigzag(const double bloc[N][N], int zigzag[N * N]);
void pgm_rle(FILE* f, const int zigzag[N * N]);
void pgm_to_jpeg(const pgm_t* in_pgm, const char* fname);
int taille_fichier(const char* fname);

// Fonctions de décompression JPEG
void inverse_zigzag(const int zigzag[N * N], double bloc[N][N]);
void pgm_idct(double bloc[N][N]);
pgm_t* jpeg_to_pgm(const char* fname);

#endif
