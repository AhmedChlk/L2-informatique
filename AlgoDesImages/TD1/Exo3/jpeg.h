#ifndef JPEG_H
#define JPEG_H
#include <stdio.h>
#include "pgm.h"
#define N 8

void pgm_extract_blk(pgm_t* inpgm, double blk[8][8], int i, int j);
void pgm_dct(double bloc[N][N]);
void pgm_quantify(double bloc[8][8], int Q[8][8]);
void pgm_zigzag(double bloc[N][N], double zigzag[N*N]);
void pgm_rle(FILE *fd, double zgzg[64]);


#endif