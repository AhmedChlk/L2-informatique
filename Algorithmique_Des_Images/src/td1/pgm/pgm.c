#include "pgm.h"
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>

/* Allocation et libération d'image PGM */
pgm_t* pgm_alloc(unsigned int height, unsigned int width, unsigned int max_value) {
    if (height == 0 || width == 0) {
        fprintf(stderr, "Les dimensions doivent être non nulles pour l'image PGM.\n");
        return NULL;
    }
    pgm_t* img = malloc(sizeof(pgm_t));
    if (img == NULL) {
        fprintf(stderr, "Erreur d'allocation mémoire pour l'image PGM.\n");
        return NULL;
    }
    img->height = height;
    img->width = width;
    img->max_value = max_value;
    img->pixels = malloc(height * sizeof(unsigned char*));
    if (img->pixels == NULL) {
        fprintf(stderr, "Erreur d'allocation mémoire pour les lignes de pixels.\n");
        free(img);
        return NULL;
    }
    for (unsigned int i = 0; i < height; i++) {
        img->pixels[i] = malloc(width * sizeof(unsigned char));
        if (img->pixels[i] == NULL) {
            fprintf(stderr, "Erreur d'allocation mémoire pour la ligne %u.\n", i);
            // Libération des ressources déjà allouées
            for (unsigned int j = 0; j < i; j++) {
                free(img->pixels[j]);
            }
            free(img->pixels);
            free(img);
            return NULL;
        }
    }
    // Initialisation de tous les pixels à la valeur maximale (blanc)
    for (unsigned int i = 0; i < height; i++) {
        for (unsigned int j = 0; j < width; j++) {
            img->pixels[i][j] = (unsigned char) max_value;
        }
    }
    return img;
}

void pgm_free(pgm_t** image) {
    if (image == NULL || *image == NULL)
        return;
    for (unsigned int i = 0; i < (*image)->height; i++) {
        free((*image)->pixels[i]);
    }
    free((*image)->pixels);
    free(*image);
    *image = NULL;
}

/* Lecture et écriture en mode ASCII (P2) */
pgm_t* pgm_read_asc(const char* fname) {
    FILE* f = fopen(fname, "r");
    if (f == NULL) {
        fprintf(stderr, "Erreur d'ouverture du fichier %s.\n", fname);
        return NULL;
    }
    char format[4];
    if (fscanf(f, "%3s", format) != 1) {
        fprintf(stderr, "Erreur de lecture du format du fichier PGM.\n");
        fclose(f);
        return NULL;
    }
    // On suppose ici que le format doit être "P2"
    if (strcmp(format, "P2") != 0) {
        fprintf(stderr, "Format PGM ASCII invalide (attendu P2, obtenu %s).\n", format);
        fclose(f);
        return NULL;
    }
    // Gestion des espaces et des commentaires
    int c = fgetc(f);
    while (c == '#' || isspace(c)) {
        if (c == '#') {
            // Passer la ligne de commentaire
            while ((c = fgetc(f)) != '\n' && c != EOF) { }
        }
        c = fgetc(f);
    }
    ungetc(c, f);
    unsigned int width, height, max_value;
    if (fscanf(f, "%u %u %u", &width, &height, &max_value) != 3) {
        fprintf(stderr, "Erreur lors de la lecture des dimensions de l'image ASCII.\n");
        fclose(f);
        return NULL;
    }
    pgm_t* image = pgm_alloc(height, width, max_value);
    if (image == NULL) {
        fclose(f);
        return NULL;
    }
    for (unsigned int i = 0; i < height; i++) {
        for (unsigned int j = 0; j < width; j++) {
            if (fscanf(f, "%hhu", &image->pixels[i][j]) != 1) {
                fprintf(stderr, "Erreur lors de la lecture du pixel [%u][%u] du fichier ASCII.\n", i, j);
                pgm_free(&image);
                fclose(f);
                return NULL;
            }
        }
    }
    fclose(f);
    return image;
}

int pgm_write_asc(const char* fname, const pgm_t* img) {
    if (img == NULL) {
        return -1;
    }
    FILE* f = fopen(fname, "w");
    if (f == NULL) {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier %s.\n", fname);
        return -1;
    }
    if (fprintf(f, "P2\n") < 0) {
        fclose(f);
        return -1;
    }
    if (fprintf(f, "# Créé par AlgoDesImages\n") < 0) {
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
            if (fprintf(f, "%hhu\n", img->pixels[i][j]) < 0) {
                fprintf(stderr, "Erreur lors de l'écriture du pixel [%u][%u] en ASCII.\n", i, j);
                fclose(f);
                return -1;
            }
        }
    }
    fclose(f);
    return 0;
}

/* Lecture et écriture en mode binaire (P5) */
pgm_t* pgm_read_bin(const char* fname) {
    FILE* f = fopen(fname, "rb");
    if (f == NULL) {
        fprintf(stderr, "Erreur d'ouverture du fichier %s.\n", fname);
        return NULL;
    }
    char format[4];
    if (fscanf(f, "%3s", format) != 1) {
        fprintf(stderr, "Erreur de lecture du format du fichier PGM binaire.\n");
        fclose(f);
        return NULL;
    }
    if (strcmp(format, "P5") != 0) {
        fprintf(stderr, "Format PGM binaire non supporté : %s (attendu P5).\n", format);
        fclose(f);
        return NULL;
    }
    // Gestion des espaces et commentaires
    int c = fgetc(f);
    while (c == '#' || isspace(c)) {
        if (c == '#') {
            while ((c = fgetc(f)) != '\n' && c != EOF) { }
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
    // Consommer le caractère de fin de ligne restant après le header
    fgetc(f);
    pgm_t* image = pgm_alloc(height, width, max_value);
    if (image == NULL) {
        fclose(f);
        return NULL;
    }
    for (unsigned int i = 0; i < height; i++) {
        size_t read = fread(image->pixels[i], sizeof(unsigned char), width, f);
        if (read != width) {
            fprintf(stderr, "Erreur de lecture de la ligne %u (lu %zu octets, attendu %u).\n", i, read, width);
            pgm_free(&image);
            fclose(f);
            return NULL;
        }
    }
    fclose(f);
    return image;
}

int pgm_write_bin(const char* fname, const pgm_t* img) {
    if (img == NULL) {
        return -1;
    }
    FILE* f = fopen(fname, "wb");
    if (f == NULL) {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier %s.\n", fname);
        return -1;
    }
    if (fprintf(f, "P5\n") < 0) {
        fclose(f);
        return -1;
    }
    if (fprintf(f, "# Créé par AlgoDesImages\n") < 0) {
        fclose(f);
        return -1;
    }
    if (fprintf(f, "%u %u\n", img->width, img->height) < 0 ||
        fprintf(f, "%u\n", img->max_value) < 0) {
        fclose(f);
        return -1;
    }
    for (unsigned int i = 0; i < img->height; i++) {
        size_t written = fwrite(img->pixels[i], sizeof(unsigned char), img->width, f);
        if (written != img->width) {
            fprintf(stderr, "Erreur d'écriture de la ligne %u (écrit %zu octets, attendu %u).\n", i, written, img->width);
            fclose(f);
            return -1;
        }
    }
    fclose(f);
    return 0;
}

/* Traitements d'image : négatif et extraction */
int pgm_negative(const pgm_t* src, pgm_t** dest) {
    if (src == NULL || dest == NULL) {
        return -1;
    }
    if (*dest != NULL) {
        pgm_free(dest);
    }
    *dest = pgm_alloc(src->height, src->width, src->max_value);
    if (*dest == NULL) {
        return -1;
    }
    for (unsigned int i = 0; i < src->height; i++) {
        for (unsigned int j = 0; j < src->width; j++) {
            (*dest)->pixels[i][j] = (unsigned char) (src->max_value - src->pixels[i][j]);
        }
    }
    return 0;
}

int pgm_extract(const char* fname, const pgm_t* image, unsigned int dx, unsigned int dy, unsigned int sub_height, unsigned int sub_width) {
    if (image == NULL || fname == NULL) {
        return -1;
    }
    if (dx > image->height || dy > image->width || sub_height == 0 || sub_width == 0 ||
        dx + sub_height > image->height || dy + sub_width > image->width) {
        fprintf(stderr, "Extraction impossible, vérifiez les paramètres.\n");
        return -1;
    }
    pgm_t* subimg = pgm_alloc(sub_height, sub_width, image->max_value);
    if (subimg == NULL) {
        return -1;
    }
    for (unsigned int i = 0; i < sub_height; i++) {
        for (unsigned int j = 0; j < sub_width; j++) {
            subimg->pixels[i][j] = image->pixels[dx + i][dy + j];
        }
    }
    int result = pgm_write_asc(fname, subimg);
    pgm_free(&subimg);
    return result;
}

/* Histogramme */
unsigned int* pgm_get_histogram(const pgm_t* image) {
    if (image == NULL) {
        return NULL;
    }
    unsigned int* histogram = malloc((image->max_value + 1) * sizeof(unsigned int));
    if (histogram == NULL) {
        fprintf(stderr, "Erreur d'allocation mémoire pour l'histogramme.\n");
        return NULL;
    }
    for (unsigned int i = 0; i <= image->max_value; i++) {
        histogram[i] = 0;
    }
    for (unsigned int i = 0; i < image->height; i++) {
        for (unsigned int j = 0; j < image->width; j++) {
            unsigned char pixel_value = image->pixels[i][j];
            histogram[pixel_value] += 1;
        }
    }
    return histogram;
}

int pgm_write_histogram(const char* fname, const pgm_t* image) {
    if (image == NULL) {
        return -1;
    }
    FILE* f = fopen(fname, "w");
    if (f == NULL) {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier %s.\n", fname);
        return -1;
    }
    unsigned int* histogram = pgm_get_histogram(image);
    if (histogram == NULL) {
        fclose(f);
        return -1;
    }
    // Écrire deux colonnes : niveau de gris et fréquence
    for (unsigned int value = 0; value <= image->max_value; value++) {
        if (fprintf(f, "%u %u\n", value, histogram[value]) < 0) {
            fprintf(stderr, "Erreur lors de l'écriture de l'histogramme.\n");
            free(histogram);
            fclose(f);
            return -1;
        }
    }
    free(histogram);
    fclose(f);
    return 0;
}
