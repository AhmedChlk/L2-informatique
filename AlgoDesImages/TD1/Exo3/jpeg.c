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

void pgm_zigzag(double bloc[N][N], int zigzag[N*N]) {
    int row = 0, col = 0;
    for (int k = 0; k < N * N; k++) {
        zigzag[k] = (int)bloc[row][col];
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

void pgm_rle(FILE *fd, int zgzg[N*N]){
    int i = 0;
    
    while (i < N*N) {
        if(zgzg[i] == 0){
            int count = 1;
            while ((i + count < N*N) && (zgzg[i] == zgzg[i + count])) {
                count++;
            }
            if (count >= 2)
                fprintf(fd, "@$%d$\n", count);
            else
                fprintf(fd, "%d\n", zgzg[i]);
            i += count;
        } else {
            fprintf(fd, "%d\n", zgzg[i]);
            i++;
        }
    }
}

void pgm_to_jpeg(pgm_t *in_pgm,char *fname){
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
    FILE* F = fopen(fname,"w");
    if(F == NULL){
        fprintf(stderr,"Erreur lors de l'ouverture du fichier %s\n",fname);
        return;
    }
    fprintf(F,"%s\n","JPEG");
    fprintf(F,"%d %d\n",in_pgm->width,in_pgm->height);
    for(int i=0;i + N<in_pgm->height;i+=N){
        for(int j=0;j + N<in_pgm->width;j+=N){
            double bloc[N][N];
            pgm_extract_blk(in_pgm,bloc,i,j);
            pgm_dct(bloc);
            pgm_quantify(bloc,Q);
            int zigzag[N*N];
            pgm_zigzag(bloc,zigzag);
            pgm_rle(F,zigzag);
        }
    }
    fclose(F);
}

int fsize(char *fname){
    FILE* F = fopen(fname,"r");
    if(F == NULL){
        fprintf(stderr,"Erreur lors de l'ouverture du fichier %s\n",fname);
        return -1;
    }
    fseek(F,0L,SEEK_END);
    int size = ftell(F);
    fclose(F);
    return size;
}

void decode_rle_jpeg(const char* fname, int*** zgzg) {
    FILE* F = fopen(fname, "r");
    if (F == NULL) {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier %s\n", fname);
        return;
    }

    char buffer[256];
    if (fscanf(F, "%4s", buffer) != 1) {
        fprintf(stderr, "Erreur de lecture du fichier %s\n", fname);
        fclose(F);
        return;
    }

    if (strcmp(buffer, "JPEG") != 0) {
        fprintf(stderr, "Erreur : le fichier %s n'est pas un fichier JPEG\n", fname);
        fclose(F);
        return;
    }

    int width, height;
    if (fscanf(F, "%d %d", &width, &height) != 2) {
        fprintf(stderr, "Erreur de lecture des dimensions\n");
        fclose(F);
        return;
    }

    int nbr_blocs = (width * height + (N * N - 1)) / (N * N);
    (*zgzg) = (int**)malloc(nbr_blocs * sizeof(int*));
    if (*zgzg == NULL) {
        fprintf(stderr, "Erreur d'allocation mémoire\n");
        fclose(F);
        return;
    }

    for (int i = 0; i < nbr_blocs; i++) {
        (*zgzg)[i] = (int*)malloc(N * N * sizeof(int));
        if ((*zgzg)[i] == NULL) {
            fprintf(stderr, "Erreur d'allocation mémoire\n");
            fclose(F);
            return;
        }
        memset((*zgzg)[i], 0, N * N * sizeof(int));
    }

    for (int i = 0; i < nbr_blocs; i++) {
        printf("DEBUG i=%d\n", i);
        int j = 0;

        while (j < N * N) {
            char val[10];
            if (fscanf(F, "%s", val) != 1) {
                fprintf(stderr, "Erreur de lecture des valeurs\n");
                fclose(F);
                return;
            }

            if (val[0] == '@') {
                int count = 0;
                if (sscanf(val, "@$%d$", &count) != 1) {
                    fprintf(stderr, "Erreur de lecture du RLE\n");
                    fclose(F);
                    return;
                }

                for (int k = 0; k < count && j < N * N; k++) {
                    (*zgzg)[i][j] = 0;
                    j++;
                }
            } else {
                (*zgzg)[i][j] = atoi(val);
                j++;
            }
        }
    }

    fclose(F);
}