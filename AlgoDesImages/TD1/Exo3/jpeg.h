#ifndef JPEG_H
#define JPEG_H
#include <stdio.h>
#include "pgm.h"
#define N 8

// JPEG Compression
void pgm_extract_blk(pgm_t* inpgm, double blk[8][8], int i, int j);
void pgm_dct(double bloc[N][N]);
void pgm_quantify(double bloc[8][8], int Q[8][8]);
void pgm_zigzag(double bloc[N][N], int zigzag[N*N]);
void pgm_rle(FILE *fd, int zgzg[64]);
void pgm_to_jpeg(pgm_t *in_pgm,char *fname);
int fsize(char* filename);
// JPEG Decompression
void decode_rle_jpeg(const char* fname,int*** zgzg);

#endif