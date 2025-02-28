#include<stdio.h>
#include"jpeg.h"
int main(){
    pgm_t* img = pgm_read_asc("eye_s_asc.pgm");
    double zigzag[N*N];
    double bloc[8][8];
    pgm_extract_blk(img,bloc,0,0);
    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){
            printf("%lf ",bloc[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    pgm_dct(bloc);
    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){
            printf("%lf ",bloc[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    printf("\n");

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
    pgm_quantify(bloc,Q);
    pgm_zigzag(bloc,zigzag);
    for(int i=0;i<N*N;i++){
        printf("%lf \n",zigzag[i]);
    }
    FILE* f = fopen("compression_rle.txt","w");
    pgm_rle(f,zigzag);
    return 0;
}