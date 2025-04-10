#include "ppm.h"
#include "pgm.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* -------------------------------------------------------------------------
   Fonction auxiliaire : écriture d'un commentaire dans le fichier
   ------------------------------------------------------------------------- */
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

/* Histogramme et conversion */
rgb_t* ppm_get_histogram(const ppm_t* image) {
    rgb_t* histogram = malloc((image->max_value + 1) * sizeof(rgb_t));
    if (histogram == NULL) {
        perror("malloc");
        return NULL;
    }
    for (unsigned int i = 0; i <= image->max_value; i++) {
        histogram[i].r = 0;
        histogram[i].g = 0;
        histogram[i].b = 0;
    }
    for (unsigned int i = 0; i < image->height; i++) {
        for (unsigned int j = 0; j < image->width; j++) {
            histogram[image->pixels[i][j].r].r++;
            histogram[image->pixels[i][j].g].g++;
            histogram[image->pixels[i][j].b].b++;
        }
    }
    return histogram;
}

int ppm_write_histogram(const char* fname, const ppm_t* image) {
    FILE* f = fopen(fname, "w");
    if (f == NULL) {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier %s.\n", fname);
        return -1;
    }
    rgb_t* histogram = ppm_get_histogram(image);
    if (histogram == NULL) {
        fprintf(stderr, "Erreur lors de la création de l'histogramme.\n");
        fclose(f);
        return -1;
    }
    for (unsigned int i = 0; i <= image->max_value; i++) {
        if (fprintf(f, "%u %u %u %u\n", i, histogram[i].r, histogram[i].g, histogram[i].b) < 0) {
            fprintf(stderr, "Erreur lors de l'écriture de l'histogramme dans le fichier.\n");
            free(histogram);
            fclose(f);
            return -1;
        }
    }
    free(histogram);
    fclose(f);
    return 0;
}

int ppm_to_pgm(const ppm_t* ppm_img, pgm_t** pgm_img) {
    if (ppm_img == NULL || pgm_img == NULL)
        return -1;
    if (*pgm_img != NULL) {
        pgm_free(pgm_img);
    }
    *pgm_img = pgm_alloc(ppm_img->height, ppm_img->width, ppm_img->max_value);
    if (*pgm_img == NULL) {
        return -1;
    }
    for (unsigned int i = 0; i < (*pgm_img)->height; i++) {
        for (unsigned int j = 0; j < (*pgm_img)->width; j++) {
            (*pgm_img)->pixels[i][j] = (unsigned char) (
                0.299 * ppm_img->pixels[i][j].r +
                0.587 * ppm_img->pixels[i][j].g +
                0.114 * ppm_img->pixels[i][j].b
            );
        }
    }
    return 0;
}
