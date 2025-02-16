#include "ppm.h"
#include "pgm.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* -------------------------------------------------------------------------
   Fonction auxiliaire : écriture d'un commentaire dans le fichier
   ------------------------------------------------------------------------- */
/**
 * Écrit un commentaire dans le fichier ouvert.
 * @param f        Pointeur sur le fichier ouvert en écriture.
 * @param comment Chaîne de caractères contenant le commentaire (optionnel).
 * @return 0 en cas de succès, -1 en cas d'erreur.
 */
int write_comment(FILE* f, const char* comment) {
    if (!f)
        return -1;
    if (comment != NULL && comment[0] != '\0') {
        if (fprintf(f, "# %s\n", comment) < 0)
            return -1;
    }
    return 0;
}

/* -------------------------------------------------------------------------
   Allocation et libération de l'image PPM
   ------------------------------------------------------------------------- */
/**
 * Alloue et initialise une image PPM.
 * Les pixels sont initialisés à la valeur maximale (blanc).
 * @param height    Hauteur de l'image.
 * @param width     Largeur de l'image.
 * @param max_value Valeur maximale d'un canal.
 * @return Pointeur sur l'image allouée ou NULL en cas d'erreur.
 */
ppm_t* ppm_alloc(unsigned int height, unsigned int width, unsigned int max_value) {
    if (height == 0 || width == 0) {
        fprintf(stderr, "Les dimensions doivent être non nulles.\n");
        return NULL;
    }
    ppm_t* img = malloc(sizeof(ppm_t));
    if (img == NULL) {
        perror("malloc");
        return NULL;
    }
    img->height = height;
    img->width = width;
    img->max_value = max_value;

    img->pixels = malloc(height * sizeof(rgb_t*));
    if (img->pixels == NULL) {
        perror("malloc");
        free(img);
        return NULL;
    }
    for (unsigned int i = 0; i < height; i++) {
        img->pixels[i] = malloc(width * sizeof(rgb_t));
        if (img->pixels[i] == NULL) {
            perror("malloc");
            for (unsigned int k = 0; k < i; k++) {
                free(img->pixels[k]);
            }
            free(img->pixels);
            free(img);
            return NULL;
        }
        /* Initialisation des pixels à max_value (blanc) */
        for (unsigned int j = 0; j < width; j++) {
            img->pixels[i][j].r = max_value;
            img->pixels[i][j].g = max_value;
            img->pixels[i][j].b = max_value;
        }
    }
    return img;
}

/**
 * Libère la mémoire associée à une image PPM.
 * @param img Pointeur sur le pointeur de l'image à libérer.
 */
void ppm_free(ppm_t** img) {
    if (img == NULL || *img == NULL)
        return;
    for (unsigned int i = 0; i < (*img)->height; i++) {
        free((*img)->pixels[i]);
    }
    free((*img)->pixels);
    free(*img);
    *img = NULL;
}

/* -------------------------------------------------------------------------
   Lecture et écriture en format ASCII (P3)
   ------------------------------------------------------------------------- */
/**
 * Lit une image PPM au format ASCII (P3) depuis un fichier.
 * @param fname Nom du fichier à lire.
 * @return Pointeur sur l'image lue ou NULL en cas d'erreur.
 */
ppm_t* ppm_read_asc(const char* fname) {
    FILE* f = fopen(fname, "r");
    if (f == NULL) {
        perror("fopen");
        return NULL;
    }
    char format[4];
    if (fscanf(f, "%3s", format) != 1) {
        fprintf(stderr, "Erreur de lecture du format.\n");
        fclose(f);
        return NULL;
    }
    if (strcmp(format, "P3") != 0) {
        fprintf(stderr, "Format invalide (attendu 'P3', trouvé '%s').\n", format);
        fclose(f);
        return NULL;
    }
    /* Saut des commentaires et espaces */
    int c = fgetc(f);
    while (c == '#' || isspace(c)) {
        if (c == '#') {
            while ((c = fgetc(f)) != '\n' && c != EOF);
        }
        c = fgetc(f);
    }
    ungetc(c, f);
    unsigned int width, height, max_value;
    if (fscanf(f, "%u %u %u", &width, &height, &max_value) != 3) {
        fprintf(stderr, "Erreur lors de la lecture des dimensions et du max_value.\n");
        fclose(f);
        return NULL;
    }
    ppm_t* img = ppm_alloc(height, width, max_value);
    if (!img) {
        fclose(f);
        return NULL;
    }
    for (unsigned int i = 0; i < img->height; i++) {
        for (unsigned int j = 0; j < img->width; j++) {
            if (fscanf(f, "%hhu %hhu %hhu", 
                       &img->pixels[i][j].r,
                       &img->pixels[i][j].g,
                       &img->pixels[i][j].b) != 3) {
                fprintf(stderr, "Erreur lors de la lecture du pixel [%u][%u].\n", i, j);
                ppm_free(&img);
                fclose(f);
                return NULL;
            }
        }
    }
    fclose(f);
    return img;
}

/**
 * Affiche les informations de l'image PPM sur la sortie standard.
 * @param img Pointeur sur l'image (non modifiée).
 */
void ppm_print(const ppm_t* img) {
    if (img == NULL)
        return;
    printf("Largeur    : %u\n", img->width);
    printf("Hauteur    : %u\n", img->height);
    printf("Max Value  : %u\n", img->max_value);
    printf("Pixels (r, g, b):\n");
    for (unsigned int i = 0; i < img->height; i++) {
        for (unsigned int j = 0; j < img->width; j++) {
            printf("pixel[%u][%u] : (%hhu, %hhu, %hhu)\n",
                   i, j,
                   img->pixels[i][j].r,
                   img->pixels[i][j].g,
                   img->pixels[i][j].b);
        }
    }
}

/**
 * Écrit une image PPM au format ASCII (P3) dans un fichier.
 * @param fname    Nom du fichier de destination.
 * @param img      Pointeur sur l'image à écrire.
 * @param comment  Commentaire à ajouter dans l'en-tête (optionnel).
 * @return 0 en cas de succès, -1 en cas d'erreur.
 */
int ppm_write_asc(const char* fname, const ppm_t* img, const char* comment) {
    if (img == NULL)
        return -1;
    FILE* f = fopen(fname, "w");
    if (f == NULL) {
        perror("fopen");
        return -1;
    }
    if (fprintf(f, "P3\n") < 0) {
        fclose(f);
        return -1;
    }
    if (write_comment(f, comment) != 0) {
        fclose(f);
        return -1;
    }
    if (fprintf(f, "%u %u\n", img->width, img->height) < 0 ||
        fprintf(f, "%u\n", img->max_value) < 0) {
        fclose(f);
        return -1;
    }
    for (unsigned int i = 0; i < img->height; i++) {
        for (unsigned int j = 0; j < img->width; j++) {
            if (fprintf(f, "%hhu %hhu %hhu\n",
                        img->pixels[i][j].r,
                        img->pixels[i][j].g,
                        img->pixels[i][j].b) < 0) {
                fclose(f);
                return -1;
            }
        }
    }
    fclose(f);
    return 0;
}

/* -------------------------------------------------------------------------
   Lecture et écriture en format binaire (P6)
   ------------------------------------------------------------------------- */
/**
 * Lit une image PPM au format binaire (P6) depuis un fichier.
 * @param fname Nom du fichier à lire.
 * @return Pointeur sur l'image lue ou NULL en cas d'erreur.
 */
ppm_t* ppm_read_bin(const char* fname) {
    FILE* f = fopen(fname, "rb");
    if (f == NULL) {
        perror("fopen");
        return NULL;
    }
    char format[4];
    if (fscanf(f, "%3s", format) != 1) {
        fprintf(stderr, "Erreur lors de la lecture du format binaire.\n");
        fclose(f);
        return NULL;
    }
    if (strcmp(format, "P6") != 0) {
        fprintf(stderr, "Format binaire invalide (attendu 'P6', trouvé '%s').\n", format);
        fclose(f);
        return NULL;
    }
    /* Saut des commentaires et espaces */
    int c = fgetc(f);
    while (c == '#' || isspace(c)) {
        if (c == '#') {
            while ((c = fgetc(f)) != '\n' && c != EOF);
        }
        c = fgetc(f);
    }
    ungetc(c, f);
    unsigned int width, height, max_value;
    if (fscanf(f, "%u %u %u", &width, &height, &max_value) != 3) {
        fprintf(stderr, "Erreur lors de la lecture des dimensions du fichier binaire.\n");
        fclose(f);
        return NULL;
    }
    /* Consommer le caractère de séparation (souvent un saut de ligne) */
    fgetc(f);
    ppm_t* img = ppm_alloc(height, width, max_value);
    if (!img) {
        fclose(f);
        return NULL;
    }
    for (unsigned int i = 0; i < img->height; i++) {
        size_t items_read = fread(img->pixels[i], sizeof(rgb_t), img->width, f);
        if (items_read != img->width) {
            fprintf(stderr, "Erreur lors de la lecture des pixels sur la ligne %u (lu %zu, attendu %u).\n",
                    i, items_read, img->width);
            ppm_free(&img);
            fclose(f);
            return NULL;
        }
    }
    fclose(f);
    return img;
}

/**
 * Écrit une image PPM au format binaire (P6) dans un fichier.
 * @param fname    Nom du fichier de destination.
 * @param img      Pointeur sur l'image à écrire.
 * @param comment  Commentaire à ajouter dans l'en-tête (optionnel).
 * @return 0 en cas de succès, -1 en cas d'erreur.
 */
int ppm_write_bin(const char* fname, const ppm_t* img, const char* comment) {
    if (img == NULL)
        return -1;
    FILE* f = fopen(fname, "wb");
    if (f == NULL) {
        perror("fopen");
        return -1;
    }
    if (fprintf(f, "P6\n") < 0) {
        fclose(f);
        return -1;
    }
    if (write_comment(f, comment) != 0) {
        fclose(f);
        return -1;
    }
    if (fprintf(f, "%u %u\n", img->width, img->height) < 0 ||
        fprintf(f, "%u\n", img->max_value) < 0) {
        fclose(f);
        return -1;
    }
    for (unsigned int i = 0; i < img->height; i++) {
        size_t items_written = fwrite(img->pixels[i], sizeof(rgb_t), img->width, f);
        if (items_written != img->width) {
            fprintf(stderr, "Erreur lors de l'écriture binaire sur la ligne %u (écrit %zu, attendu %u).\n",
                    i, items_written, img->width);
            fclose(f);
            return -1;
        }
    }
    fclose(f);
    return 0;
}

/* -------------------------------------------------------------------------
   Traitement de l'image : négatif et extraction
   ------------------------------------------------------------------------- */
/**
 * Crée l'image négative de l'image source.
 * @param src Pointeur sur l'image source (constante).
 * @param dst Adresse d'un pointeur qui recevra l'image négative.
 * @return 0 en cas de succès, -1 en cas d'erreur.
 */
int ppm_negative(const ppm_t* src, ppm_t** dst) {
    if (src == NULL || dst == NULL)
        return -1;
    if (*dst != NULL)
        ppm_free(dst);
    *dst = ppm_alloc(src->height, src->width, src->max_value);
    if (*dst == NULL)
        return -1;
    for (unsigned int i = 0; i < src->height; i++) {
        for (unsigned int j = 0; j < src->width; j++) {
            (*dst)->pixels[i][j].r = src->max_value - src->pixels[i][j].r;
            (*dst)->pixels[i][j].g = src->max_value - src->pixels[i][j].g;
            (*dst)->pixels[i][j].b = src->max_value - src->pixels[i][j].b;
        }
    }
    return 0;
}

/**
 * Extrait une sous-image d'une image PPM et l'enregistre au format ASCII (P3).
 * @param fname       Nom du fichier de destination.
 * @param image       Pointeur sur l'image source (non modifiée).
 * @param dx          Coordonnée verticale de départ dans l'image source.
 * @param dy          Coordonnée horizontale de départ dans l'image source.
 * @param sub_height  Hauteur de la sous-image.
 * @param sub_width   Largeur de la sous-image.
 * @param comment     Commentaire à ajouter dans l'en-tête du fichier extrait (optionnel).
 * @return 0 en cas de succès, -1 en cas d'erreur.
 */
int ppm_extract(const char* fname, const ppm_t* image, int dx, int dy, int sub_height, int sub_width, const char* comment) {
    if (image == NULL || fname == NULL)
        return -1;
    if (dx < 0 || dy < 0 || sub_height <= 0 || sub_width <= 0 ||
        (unsigned int)(dx + sub_height) > image->height ||
        (unsigned int)(dy + sub_width) > image->width) {
        fprintf(stderr, "Extraction impossible, vérifiez les paramètres.\n");
        return -1;
    }
    ppm_t* subimg = ppm_alloc(sub_height, sub_width, image->max_value);
    if (subimg == NULL)
        return -1;
    for (unsigned int i = 0; i < (unsigned int)sub_height; i++) {
        for (unsigned int j = 0; j < (unsigned int)sub_width; j++) {
            subimg->pixels[i][j] = image->pixels[dx + i][dy + j];
        }
    }
    int res = ppm_write_asc(fname, subimg, comment);
    ppm_free(&subimg);
    return res;
}

/**
 * recupere l'histogram de Chaque Composante (r,g,b) de l'image
 * @param image       Pointeur sur l'image.
 * @return  pointeur sur un tableau de rgb_t
 */
rgb_t* ppm_get_histogram(const ppm_t* image) { 
    rgb_t* histogram = malloc((image->max_value + 1) * sizeof(rgb_t));
    if (histogram == NULL) {
        perror("malloc");
        return NULL;
    }        

    for (unsigned i = 0; i <= image->max_value; i++) {
        histogram[i].r = 0;
        histogram[i].g = 0;
        histogram[i].b = 0;
    }

    for (unsigned i = 0; i < image->height; i++) {
        for (unsigned j = 0; j < image->width; j++) {
            histogram[image->pixels[i][j].r].r++;
            histogram[image->pixels[i][j].g].g++;
            histogram[image->pixels[i][j].b].b++;
        }
    }

    return histogram;
}

int ppm_write_histogram(const char* fname,const ppm_t* image){
    FILE* F = fopen(fname,"w");
    if(F == NULL){
        fprintf(stderr,"erreur ouverture fichier");
        return -1;
    }
    rgb_t* histogram = ppm_get_histogram(image);
    if(histogram == NULL){
        fprintf(stderr,"erreur creation histograme");
        fclose(F);
        return -1;
    }
    for(unsigned int i=0;i<=image->max_value;i++){
        if(fprintf(F,"%u %hhu %hhu %hhu\n",i,histogram[i].r,histogram[i].g,histogram[i].b) < 0){
            fprintf(stderr,"erreur ecriture fichier");
            fclose(F);
            return -1;
        }
    }
    fclose(F);
    return 0;
}

int ppm_to_pgm(ppm_t* ppm_img,pgm_t** pgm_img){
    if((*pgm_img) != NULL){
        pgm_free(&(*pgm_img));
    }
    if(((*pgm_img) = pgm_alloc(ppm_img->height,ppm_img->width,ppm_img->max_value)) == NULL){
        return -1;
    }
    for(int i=0;i<(*pgm_img)->height;i++){
        for(int j=0;j<(*pgm_img)->width;j++){
            (*pgm_img)->pixels[i][j] = (unsigned char)((float)(0.299 * ppm_img->pixels[i][j].r) + (float)(0.587 * ppm_img->pixels[i][j].g) + (float)(0.114 * ppm_img->pixels[i][j].b));
        }
    }
    return 0;
}