#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pgm.h"

int main() {
    printf("[Test PGM] Démarrage des tests du module PGM\n"); 

    // 1. Création d'une image PGM factice
    unsigned int width = 5, height = 4, max_val = 9;
    pgm_t* image = pgm_alloc(height, width, max_val);
    if (!image) {
        fprintf(stderr, "\nEchec allocation PGM initiale\n");
        return 1;
    }
    // Remplir l'image avec des valeurs (par exemple, valeur = (i * width + j) mod (max_val+1))
    for (unsigned int i = 0; i < height; i++) {
        for (unsigned int j = 0; j < width; j++) {
            image->pixels[i][j] = (unsigned char) ((i * width + j) % (max_val + 1));
        }
    }
    printf("Image PGM initiale: %u x %u, max_value=%u. Exemple pixel[0][0]=%d, pixel[%d][%d]=%d\n",
           width, height, max_val, image->pixels[0][0], height-1, width-1, image->pixels[height-1][width-1]);

    // 2. Test de l'écriture et lecture ASCII
    const char* file_asc = "test_output.pgm";
    if (pgm_write_asc(file_asc, image) != 0) {
        fprintf(stderr, "Erreur lors de l'écriture ASCII de l'image PGM\n");
    } else {
        pgm_t* image_read = pgm_read_asc(file_asc);
        if (!image_read) {
            fprintf(stderr, "Erreur lors de la lecture ASCII de l'image PGM\n");
        } else {
            printf("Lecture ASCII réussie: dimensions lues = %u x %u, max_value=%u\n",
                   image_read->height, image_read->width, image_read->max_value);
            printf("Valeur pixel[0][0] lue = %d (attendu %d)\n",
                   image_read->pixels[0][0], image->pixels[0][0]);
            pgm_free(&image_read);
        }
    }

    // 3. Test de l'écriture et lecture binaire
    const char* file_bin = "test_output_bin.pgm";
    if (pgm_write_bin(file_bin, image) != 0) {
        fprintf(stderr, "Erreur lors de l'écriture binaire de l'image PGM\n");
    } else {
        pgm_t* image_read2 = pgm_read_bin(file_bin);
        if (!image_read2) {
            fprintf(stderr, "Erreur lors de la lecture binaire de l'image PGM\n");
        } else {
            printf("Lecture binaire réussie: dimensions lues = %u x %u, max_value=%u\n",
                   image_read2->height, image_read2->width, image_read2->max_value);
            printf("Valeur pixel[%d][%d] lue = %d (attendu %d)\n",
                   height-1, width-1, image_read2->pixels[height-1][width-1], image->pixels[height-1][width-1]);
            pgm_free(&image_read2);
        }
    }

    // 4. Test de pgm_negative
    pgm_t* neg_image = NULL;
    if (pgm_negative(image, &neg_image) == 0) {
        printf("Négatif calculé. Exemples: pixel[0][0]=%d devient %d, pixel[%d][%d]=%d devient %d\n",
               image->pixels[0][0], neg_image->pixels[0][0],
               height-1, width-1, image->pixels[height-1][width-1], neg_image->pixels[height-1][width-1]);
        pgm_free(&neg_image);
    } else {
        fprintf(stderr, "Erreur lors de la création du négatif PGM\n");
    }

    // 5. Test de pgm_extract
    unsigned int sub_h = 2, sub_w = 3;
    unsigned int dx = 1, dy = 1;
    const char* extract_file = "test_extract.pgm";
    if (pgm_extract(extract_file, image, dx, dy, sub_h, sub_w) == 0) {
        pgm_t* extracted = pgm_read_asc(extract_file);
        if (extracted) {
            printf("Extraction réussie (%ux%u depuis [%u,%u]). Dimensions extraites: %u x %u\n",
                   sub_h, sub_w, dx, dy, extracted->height, extracted->width);
            printf("Valeur pixel[0][0] extrait = %d (original image[%u][%u]=%d)\n",
                   extracted->pixels[0][0], dx, dy, image->pixels[dx][dy]);
            pgm_free(&extracted);
        } else {
            fprintf(stderr, "Erreur lecture fichier extrait\n");
        }
    } else {
        fprintf(stderr, "Erreur lors de l'extraction PGM\n");
    }

    // 6. Test de pgm_get_histogram et pgm_write_histogram
    unsigned int* histo = pgm_get_histogram(image);
    if (histo) {
        // Compter le nombre total de pixels via l'histogramme pour vérifier
        unsigned int total_pixels = 0;
        for (unsigned int v = 0; v <= image->max_value; ++v) {
            total_pixels += histo[v];
        }
        printf("Histogramme calculé. Total pixels comptés = %u (attendu %u)\n", total_pixels, width*height);
        free(histo);
    } else {
        fprintf(stderr, "Erreur lors du calcul de l'histogramme PGM\n");
    }
    if (pgm_write_histogram("test_histogram_pgm.txt", image) == 0) {
        printf("Histogramme écrit dans 'test_histogram_pgm.txt'.\n");
    }

    // Libérer l'image initiale
    pgm_free(&image);
    printf("[Test PGM] Fin des tests du module PGM\n");
    return 0;
}
