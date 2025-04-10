#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ppm.h"

int main() {
    printf("[Test PPM] Démarrage des tests du module PPM\n");

    // 1. Création d'une image PPM factice
    unsigned int width = 3, height = 2, max_val = 5;
    ppm_t* image = ppm_alloc(height, width, max_val);
    if (!image) {
        fprintf(stderr, "Echec allocation PPM initiale\n");
        return 1;
    }
    // Remplir l'image avec quelques couleurs
    // Exemple : pixel (i,j) -> r = i, g = j, b = (i+j) mod (max_val+1)
    for (unsigned int i = 0; i < height; i++) {
        for (unsigned int j = 0; j < width; j++) {
            image->pixels[i][j].r = (unsigned char) i;
            image->pixels[i][j].g = (unsigned char) j;
            image->pixels[i][j].b = (unsigned char) ((i + j) % (max_val + 1));
        }
    }
    printf("Image PPM initiale: %u x %u, max_value=%u. Exemple pixel[0][0]=(r=%d,g=%d,b=%d)\n",
           width, height, max_val,
           image->pixels[0][0].r, image->pixels[0][0].g, image->pixels[0][0].b);

    // 2. Test de l'écriture et lecture ASCII (P3)
    const char* file_asc = "test_output.ppm";
    if (ppm_write_asc(file_asc, image, "Commentaire de test") != 0) {
        fprintf(stderr, "Erreur lors de l'écriture ASCII de l'image PPM\n");
    } else {
        ppm_t* image_read = ppm_read_asc(file_asc);
        if (!image_read) {
            fprintf(stderr, "Erreur lors de la lecture ASCII de l'image PPM\n");
        } else {
            printf("Lecture ASCII réussie: dimensions lues = %u x %u, max_value=%u\n",
                   image_read->height, image_read->width, image_read->max_value);
            printf("Valeur pixel[%d][%d] lue = (r=%d,g=%d,b=%d) (attendu r=%d,g=%d,b=%d)\n",
                   height-1, width-1,
                   image_read->pixels[height-1][width-1].r,
                   image_read->pixels[height-1][width-1].g,
                   image_read->pixels[height-1][width-1].b,
                   image->pixels[height-1][width-1].r,
                   image->pixels[height-1][width-1].g,
                   image->pixels[height-1][width-1].b);
            ppm_free(&image_read);
        }
    }

    // 3. Test de l'écriture et lecture binaire (P6)
    const char* file_bin = "test_output_bin.ppm";
    if (ppm_write_bin(file_bin, image, NULL) != 0) {
        fprintf(stderr, "Erreur lors de l'écriture binaire de l'image PPM\n");
    } else {
        ppm_t* image_read2 = ppm_read_bin(file_bin);
        if (!image_read2) {
            fprintf(stderr, "Erreur lors de la lecture binaire de l'image PPM\n");
        } else {
            printf("Lecture binaire réussie: dimensions lues = %u x %u, max_value=%u\n",
                   image_read2->height, image_read2->width, image_read2->max_value);
            printf("Valeur pixel[0][0] lue = (r=%d,g=%d,b=%d) (attendu r=%d,g=%d,b=%d)\n",
                   image_read2->pixels[0][0].r, image_read2->pixels[0][0].g, image_read2->pixels[0][0].b,
                   image->pixels[0][0].r, image->pixels[0][0].g, image->pixels[0][0].b);
            ppm_free(&image_read2);
        }
    }

    // 4. Test de ppm_negative
    ppm_t* neg_image = NULL;
    if (ppm_negative(image, &neg_image) == 0) {
        printf("Négatif calculé. Exemple pixel[0][0] devient (r=%d,g=%d,b=%d) (était r=%d,g=%d,b=%d)\n",
               neg_image->pixels[0][0].r, neg_image->pixels[0][0].g, neg_image->pixels[0][0].b,
               image->pixels[0][0].r, image->pixels[0][0].g, image->pixels[0][0].b);
        ppm_free(&neg_image);
    } else {
        fprintf(stderr, "Erreur lors de la création du négatif PPM\n");
    }

    // 5. Test de conversion ppm_to_pgm
    pgm_t* gray_image = NULL;
    if (ppm_to_pgm(image, &gray_image) == 0) {
        printf("Conversion PPM->PGM réussie: dimensions = %u x %u, max_value=%u\n",
               gray_image->height, gray_image->width, gray_image->max_value);
        printf("Exemple pixel[0][0] gris = %d (à partir de r=%d,g=%d,b=%d)\n",
               gray_image->pixels[0][0], image->pixels[0][0].r, image->pixels[0][0].g, image->pixels[0][0].b);
        pgm_free(&gray_image);
    } else {
        fprintf(stderr, "Erreur conversion ppm_to_pgm\n");
    }

    // 6. Test de histogramme PPM
    rgb_t* histo = ppm_get_histogram(image);
    if (histo) {
        // On peut afficher par exemple le nombre de pixels de valeur 0 pour r, g, b
        printf("Histogramme: Pixels de valeur 0 -> R:%u G:%u B:%u\n", histo[0].r, histo[0].g, histo[0].b);
        free(histo);
    }
    if (ppm_write_histogram("test_histogram_ppm.txt", image) == 0) {
        printf("Histogramme PPM écrit dans 'test_histogram_ppm.txt'.\n");
    }

    // Libérer l'image initiale
    ppm_free(&image);
    printf("[Test PPM] Fin des tests du module PPM\n");
    return 0;
}
