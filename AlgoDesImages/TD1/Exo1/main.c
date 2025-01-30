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
    for(int i=0;i<(int)image->height;i++){
        free(image->pixels[i]);
        //printf("liberation de la ligne %d\n",i+1);
    }
    free(image->pixels);
    image->pixels = NULL;
    printf("liberation avec succes\n");
}
pgm_t* pgm_read_asc(const char* fname){
    FILE* F = fopen(fname,"r");
    if(F == NULL){
        fprintf(stderr, "Erreur d'ouverture du ficher.\n");
        exit(EXIT_FAILURE);
    }
    char format[3];
    fscanf(F,"%s",format);
    printf("%s\n",format);

    char c = fgetc(F);
    c = fgetc(F);
    while(c == '#'){
        while(c != '\n' && c != EOF){
            printf("%c",c);
            c = fgetc(F);
        }
        c = fgetc(F);
        printf("\n");
    }
    ungetc(c,F);
    unsigned int height,width,max_value;
    fscanf(F,"%u %u %u",&width,&height,&max_value);
    printf(" width : %u height :  %u max value :%u\n",width,height,max_value);
    pgm_t image = pgm_alloc(height,width,max_value);
    for(int i=0;i<height;i++){
        for(int j=0;j<width;j++){
            fscanf(F,"%u",&image.pixels[i][j]);
        }
    }
    pgm_t* img = (pgm_t*) malloc (sizeof(pgm_t));
    *img = image;
    return img;

}

void pgm_write_asc(const char* fname,pgm_t* img){

}
int main(void) {
    pgm_t* image = pgm_read_asc("eye_s_asc.pgm");
    for(int i=0;i<image->height;i++){
        for(int j=0;j<image->width;j++){
            printf("%u ",image->pixels[i][j]);

        }
        printf("\n");
    }
    return 0;
}
