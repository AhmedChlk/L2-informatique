#ifndef JPEG_H
#define JPEG_H

#include <stdio.h>
#include "pgm.h"

#define N 8

// Fonctions de compression JPEG
void pgm_extract_blk(pgm_t* inpgm, double blk[N][N], int i, int j);
void pgm_dct(double bloc[N][N]);
void pgm_quantify(double bloc[N][N], int Q[N][N]);
void pgm_zigzag(double bloc[N][N], int zigzag[N*N]);
void pgm_rle(FILE *fd, int zgzg[N*N]);
void pgm_to_jpeg(pgm_t *in_pgm, char *fname);
int fsize(char *filename);

// Fonctions de décompression JPEG
void inverse_zigzag(int zigzag[N*N], double bloc[N][N]);
void pgm_idct(double bloc[N][N]);
pgm_t* jpeg_to_pgm(char *fname);

#endif
