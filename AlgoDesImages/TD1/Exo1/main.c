#include <stdio.h>
#include <stdlib.h>

typedef struct {
    unsigned int height;
    unsigned int width;
    unsigned int max_value;
    unsigned char **pixels; 
} pgm_t;

pgm_t pgm_alloc(unsigned int height, unsigned int width, unsigned int max_value) {
    pgm_t img;
    img.height = height;
    img.width = width;
    img.max_value = max_value;

    img.pixels = (unsigned char**) malloc(height * sizeof(unsigned char*));
    if (img.pixels == NULL) {
        fprintf(stderr, "Erreur d'allocation mémoire pour les lignes.\n");
        exit(EXIT_FAILURE);
    }

    for (unsigned int i = 0; i < height; i++) {
        img.pixels[i] = (unsigned char*) malloc(width * sizeof(unsigned char));
        if (img.pixels[i] == NULL) {
            fprintf(stderr, "Erreur d'allocation mémoire pour la ligne %u.\n", i);
            exit(EXIT_FAILURE);
        }
    }

    for (unsigned int i = 0; i < height; i++) {
        for (unsigned int j = 0; j < width; j++) {
            img.pixels[i][j] = (unsigned char) max_value;
        }
    }

    return img;
}

void pgm_free(pgm_t* image){
    for(int i=0;i<image->height;i++){
        free(image->pixels[i]);
        //printf("liberation de la ligne %d\n",i+1);
    }
    free(image->pixels);
    image->pixels = NULL;
    printf("liberation avec succes\n");
}
pgm_t* pgm_read_asc(const char* fname){
    pgm_t image;
    FILE* F = fopen(fname,"r");
    if(F == NULL){
        fprintf(stderr, "Erreur d'ouverture du ficher.\n");
        exit(EXIT_FAILURE);
    }
    unsigned int height,width,max_value;
    char format[3];
    fscanf(F,"%s %u %u %u",format,&width,&height,&max_value);
    image = pgm_alloc(height,width,max_value);
    pgm_t* image;
    *image = image
    for(int i=0;i<height;i++){
        for(int j=0;j<width;j++){
            fscanf(F,"%c",&(image->pixels[i][j]));
        }
    }
    return image;
}
int main(void) {
    pgm_t* image = pgm_read_asc("eye_s_asc.pgm");

    for (unsigned int i = 0; i < image->height; i++) {
        for (unsigned int j = 0; j < image->width; j++) {
            printf("%3d ", image->pixels[i][j]);
        }
        printf("\n");
    }
    pgm_free(image);
    return 0;
}
