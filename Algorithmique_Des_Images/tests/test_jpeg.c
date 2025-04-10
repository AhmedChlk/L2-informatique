#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "jpeg.h"  // inclut pgm.h

int main() {
    printf("[Test JPEG] Démarrage des tests du module JPEG\n");

    // 1. Créer une image PGM 8x8 remplie de zéros
    unsigned int size = 8;
    pgm_t* image = pgm_alloc(size, size, 255);
    if (!image) {
        fprintf(stderr, "Echec allocation image PGM pour test JPEG\n");
        return 1;
    }
    for (unsigned int i = 0; i < size; i++) {
        for (unsigned int j = 0; j < size; j++) {
            image->pixels[i][j] = 0;
        }
    }
    printf("Image PGM de test (8x8) initialisée à 0.\n");

    // 2. Compression JPEG (pgm_to_jpeg)
    const char* jpeg_file = "test_compress.txt";
    pgm_to_jpeg(image, jpeg_file);
    printf("Image compressée en %s.\n", jpeg_file);

    // Afficher la taille du fichier compressé
    int comp_size = taille_fichier(jpeg_file);
    if (comp_size >= 0) {
        printf("Taille du fichier compressé: %d octets.\n", comp_size);
    }

    // 3. Décompression JPEG (jpeg_to_pgm)
    pgm_t* image_decomp = jpeg_to_pgm(jpeg_file);
    if (!image_decomp) {
        fprintf(stderr, "Erreur lors de la décompression JPEG\n");
    } else {
        printf("Image décompressée: dimensions = %u x %u, max_value=%u\n",
               image_decomp->height, image_decomp->width, image_decomp->max_value);
        // Vérifier quelques pixels (tous devraient être 0 si tout s'est bien passé)
        printf("Exemple pixel[0][0] décompressé = %d (attendu ~0)\n", image_decomp->pixels[0][0]);
        printf("Exemple pixel[%d][%d] décompressé = %d (attendu ~0)\n",
               size-1, size-1, image_decomp->pixels[size-1][size-1]);
        pgm_free(&image_decomp);
    }

    // 4. Comparaison de taille de fichier entre PGM ASCII et fichier compressé
    const char* pgm_file = "test_original.pgm";
    pgm_write_asc(pgm_file, image);
    int pgm_size = taille_fichier(pgm_file);
    if (pgm_size >= 0) {
        printf("Taille du fichier PGM ASCII original: %d octets.\n", pgm_size);
        if (comp_size >= 0) {
            double ratio = (double) pgm_size / (double) comp_size;
            printf("Ratio de compression (ASCII PGM / JPEG texte) ~ %.2f\n", ratio);
        }
    }

    pgm_free(&image);
    printf("[Test JPEG] Fin des tests du module JPEG\n");
    return 0;
}
