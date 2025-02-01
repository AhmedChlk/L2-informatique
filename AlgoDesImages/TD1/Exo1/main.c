#include "pgm.h"


int main(void) {
    // Exemple d'utilisation pour le format ASCII
    pgm_t* image = pgm_read_asc("eye_s_asc.pgm");
    pgm_t* image_neg = NULL;
    //test de pgm_negative
    pgm_negative(image, &image_neg);
    pgm_write_asc("eye_s_asc_neg.pgm", image_neg);
    // test de l'extraction
    pgm_extract("eye_s_asc_ext.pgm", image, 0, 0, 256, 256);

    //test du stockage en binaire
    pgm_write_bin("eye_s_bin.pgm",image);

    //test du la lecture depuis un fichier binaire;
    pgm_t* image_bin = pgm_read_bin("eye_s_bin.pgm");
    pgm_write_asc("eye_s_asc_from_bin.pgm",image_bin);

    pgm_write_histogram("eye_s_asc_hist.txt",image);


    // Liberation de la memoire alloué 
    pgm_free(image);
    pgm_free(image_bin);
    pgm_free(image_neg);

    return 0;
}
