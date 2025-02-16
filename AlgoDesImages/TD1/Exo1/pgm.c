#include "pgm.h"


pgm_t* pgm_alloc(unsigned int height, unsigned int width, unsigned int max_value) {
    pgm_t* img = (pgm_t*) malloc(sizeof(pgm_t));
    if (img == NULL) {
        fprintf(stderr, "Erreur d'allocation mémoire pour l'image pgm.\n");
        return NULL;
    }
    img->height = height;
    img->width = width;
    img->max_value = max_value;

    img->pixels = (unsigned char**) malloc(height * sizeof(unsigned char*));
    if (img->pixels == NULL) {
        fprintf(stderr, "Erreur d'allocation mémoire pour les lignes.\n");
        free(img);
        return NULL;

    }

    for (unsigned int i = 0; i < height; i++) {
        img->pixels[i] = (unsigned char*) malloc(width * sizeof(unsigned char));
        if (img->pixels[i] == NULL) {
            fprintf(stderr, "Erreur d'allocation mémoire pour la ligne %u.\n", i);
            // Libérer ce qui a déjà été alloué
            for (unsigned int j = 0; j < i; j++) {
                free(img->pixels[j]);
            }
            free(img->pixels);
            free(img);
            return NULL;

        }
    }

    for (unsigned int i = 0; i < height; i++) {
        for (unsigned int j = 0; j < width; j++) {
            img->pixels[i][j] = (unsigned char) max_value;
        }
    }
    return img;
}

void pgm_free(pgm_t** image) {
    if ((*image) == NULL)
        return;
    for (unsigned int i = 0; i < (*image)->height; i++){
        free((*image)->pixels[i]);
    }
    free((*image)->pixels);
    free((*image));
    *image = NULL;
}

/* *******************************
   Lecture en mode ASCII (P2)
   ******************************* */
pgm_t* pgm_read_asc(const char* fname){
    FILE* F = fopen(fname, "r");
    if(F == NULL){
        fprintf(stderr, "Erreur d'ouverture du fichier %s.\n", fname);
        exit(EXIT_FAILURE);
    }
    char format[4];
    fscanf(F, "%3s", format);
    // On suppose ici que le format est "P2"

    int c = fgetc(F);
    // Gestion des commentaires et des espaces
    while (c == '#' || isspace(c)) {
        if(c == '#'){
            while((c = fgetc(F)) != '\n' && c != EOF)
                ; // on saute la ligne de commentaire
        }
        c = fgetc(F);
    }
    ungetc(c, F);

    unsigned int height, width, max_value;
    if(fscanf(F, "%u %u %u", &width, &height, &max_value) != 3) {
        fprintf(stderr, "Erreur lors de la lecture des dimensions.\n");
        fclose(F);
        exit(EXIT_FAILURE);
    }
    pgm_t* image = pgm_alloc(height, width, max_value);
    for(unsigned int i = 0; i < height; i++){
        for(unsigned int j = 0; j < width; j++){
            if(fscanf(F, "%hhu", &image->pixels[i][j]) != 1) {
                fprintf(stderr, "Erreur lors de la lecture des pixels à [%u][%u].\n", i, j);
                fclose(F);
                exit(EXIT_FAILURE);
            }
        }
    }
    fclose(F);
    return image;
}

int pgm_write_asc(const char* fname, pgm_t* img){
    FILE* F = fopen(fname, "w");
    if(F == NULL){
        fprintf(stderr, "Erreur d'ouverture du fichier %s.\n", fname);
        exit(EXIT_FAILURE);
    }
    fprintf(F, "P2\n");
    fprintf(F, "# Ceci est un commentaire\n");
    fprintf(F, "%u %u\n", img->width, img->height);
    fprintf(F, "%u\n", img->max_value);
    for(unsigned int i = 0; i < img->height; i++){
        for(unsigned int j = 0; j < img->width; j++){
            fprintf(F, "%hhu\n", img->pixels[i][j]);
        }
    }
    fclose(F);
    return 0;
}

/* ***************************************
   Lecture en mode binaire (P5) corrigée
   *************************************** */
pgm_t* pgm_read_bin(const char* fname) {
    FILE* F = fopen(fname, "rb");
    if(F == NULL){
        fprintf(stderr, "Erreur d'ouverture du fichier %s.\n", fname);
        exit(EXIT_FAILURE);
    }

    char format[4];
    if (fscanf(F, "%3s", format) != 1) {
        fprintf(stderr, "Erreur de lecture du format.\n");
        fclose(F);
        exit(EXIT_FAILURE);
    }
    // On s'assure que le format est "P5" pour un fichier binaire PGM
    if (strcmp(format, "P5") != 0) {
        fprintf(stderr, "Format non supporté : %s (attendu P5)\n", format);
        fclose(F);
        exit(EXIT_FAILURE);
    }

    int c = fgetc(F);
    // Sauter les espaces et commentaires
    while (c == '#' || isspace(c)) {
        if (c == '#') {
            while((c = fgetc(F)) != '\n' && c != EOF)
                ;
        }
        c = fgetc(F);
    }
    ungetc(c, F);

    unsigned int width, height, max_value;
    if (fscanf(F, "%u %u %u", &width, &height, &max_value) != 3) {
        fprintf(stderr, "Erreur lors de la lecture des dimensions du fichier binaire.\n");
        fclose(F);
        exit(EXIT_FAILURE);
    }
    // Consommation d'un caractère (souvent un saut de ligne) après le header
    fgetc(F);

    pgm_t* image = pgm_alloc(height, width, max_value);
    for (unsigned int i = 0; i < height; i++) {
        size_t lu = fread(image->pixels[i], sizeof(unsigned char), width, F);
        if (lu != width) {
            fprintf(stderr, "Erreur de lecture de la ligne %u (lu : %zu, attendu : %u).\n", i, lu, width);
            fclose(F);
            exit(EXIT_FAILURE);
        }
    }
    fclose(F);
    return image;
}

/* *****************************************
   Écriture en mode binaire (P5) corrigée
   ***************************************** */
int pgm_write_bin(const char* fname, pgm_t* img) {
    FILE* F = fopen(fname, "wb");
    if(F == NULL){
        fprintf(stderr, "Erreur d'ouverture du fichier %s.\n", fname);
        exit(EXIT_FAILURE);
    }
    // Écriture de l'en-tête pour un fichier PGM binaire (P5)
    fprintf(F, "P5\n");
    fprintf(F, "# Créé par mon programme\n");
    fprintf(F, "%u %u\n", img->width, img->height);
    fprintf(F, "%u\n", img->max_value);

    // Écriture des pixels en mode binaire
    for (unsigned int i = 0; i < img->height; i++) {
        size_t ecrit = fwrite(img->pixels[i], sizeof(unsigned char), img->width, F);
        if (ecrit != img->width) {
            fprintf(stderr, "Erreur d'écriture de la ligne %u (écrit : %zu, attendu : %u).\n", i, ecrit, img->width);
            fclose(F);
            exit(EXIT_FAILURE);
        }
    }
    fclose(F);
    return 0;
}

/* *******************************
    Écrire la fonction pgm_negative qui prendra en paramètre un pointeur scr sur une structure
    pgm contenant l’image source et un pointeur dst sur une structure pgm contenant le négatif de
    l’image source
   ******************************* */
void pgm_negative(pgm_t* src, pgm_t** dest) {
    *dest = pgm_alloc(src->height, src->width, src->max_value);
    for (unsigned int i = 0; i < src->height; i++){
        for (unsigned int j = 0; j < src->width; j++){
            (*dest)->pixels[i][j] = (unsigned char)(src->max_value - src->pixels[i][j]);
        }
    }
}

void pgm_extract(const char* fname, pgm_t* image, unsigned int dx, unsigned int dy, unsigned int width, unsigned int height) {
    if((int)image->height - (int)dx < (int)height || (int)image->width - (int)dy < (int)width) {
        printf("Extraction impossible, vérifiez vos paramètres.\n");
        return;
    } else {
        pgm_t* temp = pgm_alloc(height, width, image->max_value);
        for (unsigned int i = 0; i < height; i++){
            for (unsigned int j = 0; j < width; j++){
                temp->pixels[i][j] = image->pixels[dx + i][dy + j];
            }
        }
        pgm_write_asc(fname, temp);
        pgm_free(&temp);
    }
}

/***********************
    Écrire la fonction pgm_get_histrogram qui prendra en paramètre un pointeur sur une structure
    pgm et qui retournera un pointeur sur un tableu de max_value contenant l’histogramme des pixels
    de l’image.
 ***********************/
 unsigned int* pgm_get_histrogram(pgm_t* image){
    unsigned int* histogram = (unsigned int*) malloc(image->max_value * sizeof(unsigned int));
    for(int i=0;i<image->max_value;i++){
        histogram[i] = 0;
    }
    for(int i=0;i<image->height;i++){
        for(int j=0;j<image->width;j++){
            histogram[image->pixels[i][j]-1]++;
        }
    }
    return histogram;
 }

 /***********************
    Écrire la fonction pgm_write_histogram qui prendra en paramètre un pointeur sur une structure
    pgm, un pointeur sur une chaine de caractère fname. La fonction devra créer le fichier fname et
    l’histogramme de l’image sous la forme de deux colonnes (la première colonne contiendra les valeurs
    de 0 à max_value, la seconde les données de l’histogramme correspondant)
 ***********************/
 void pgm_write_histogram(const char* fname , pgm_t* image){
    FILE* F = fopen(fname,"w");
    if(F == NULL){
        fprintf(stderr,"erreur lors de la l'ouverturer du Fichier");
        exit(EXIT_FAILURE);
    }
    unsigned int* histogram = pgm_get_histrogram(image);
    for(int i=0;i<image->max_value;i++){
        fprintf(F,"%d %u\n",i+1,histogram[i]);
    }
    fclose(F);
 }
