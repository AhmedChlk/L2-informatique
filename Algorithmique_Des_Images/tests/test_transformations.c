#include <stdio.h>
#include <math.h>
#include "transformations.h"  // inclut pgm.h et ppm.h

int main() {
    printf("[Test Transformations] Démarrage des tests du module Transformations\n");

    // 1. Tests des fonctions B0, B1, B2, B3
    double test_vals[] = { -1.2, -0.5, 0.0, 0.3, 0.8, 1.5 };
    printf("Tests des fonctions B-splines:\n");
    for (int k = 0; k < 6; ++k) {
        double x = test_vals[k];
        printf("x=%.2f: B0=%.2f, B1=%.2f, B2=%.2f, B3=%.2f\n",
               x, B0(x), B1(x), B2(x), B3(x));
    }

    // 2. Test de interpolation_pgm
    pgm_t* pgm_img = pgm_alloc(2, 2, 255);
    pgm_img->pixels[0][0] = 0;
    pgm_img->pixels[0][1] = 0;
    pgm_img->pixels[1][0] = 0;
    pgm_img->pixels[1][1] = 255;
    unsigned char inter_val = interpolation_pgm(pgm_img, 0.5, 0.5);
    printf("Interpolation PGM au centre d'une image 2x2 (coin sup.gauche 0, coin inf.droit 255): %d (attendu ~64)\n", inter_val);

    // 3. Test de interpolation_ppm
    ppm_t* ppm_img = ppm_alloc(2, 2, 255);
    // Coin sup.gauche = rouge (100,0,0), autres noirs
    ppm_img->pixels[0][0].r = 100; ppm_img->pixels[0][0].g = 0; ppm_img->pixels[0][0].b = 0;
    ppm_img->pixels[0][1].r = ppm_img->pixels[1][0].r = ppm_img->pixels[1][1].r = 0;
    ppm_img->pixels[0][1].g = ppm_img->pixels[1][0].g = ppm_img->pixels[1][1].g = 0;
    ppm_img->pixels[0][1].b = ppm_img->pixels[1][0].b = ppm_img->pixels[1][1].b = 0;
    rgb_t inter_col = interpolation_ppm(ppm_img, 0.5, 0.5);
    printf("Interpolation PPM au centre (avec coin (0,0)=(100,0,0)): (r=%d,g=%d,b=%d) (attendu ~25,0,0)\n",
           inter_col.r, inter_col.g, inter_col.b);

    // 4. Test de rotation_pgm (180 degrés)
    pgm_t* pgm_img2 = pgm_alloc(3, 3, 9);
    // Remplir l'image 3x3 avec 1,2,3 / 4,5,6 / 7,8,9
    unsigned char val = 1;
    for (unsigned int i = 0; i < 3; ++i) {
        for (unsigned int j = 0; j < 3; ++j) {
            pgm_img2->pixels[i][j] = val++;
        }
    }
    pgm_t* rot_img = rotation_pgm(pgm_img2, M_PI, 1, 1);  // rotation 180 autour du centre (1,1)
    if (rot_img) {
        printf("Rotation 180 degrés PGM: pixel[0][0] = %d (attendu 9), pixel[2][2] = %d (attendu 1)\n",
               rot_img->pixels[0][0], rot_img->pixels[2][2]);
        pgm_free(&rot_img);
    } else {
        printf("Rotation PGM a retourné NULL\n");
    }

    // 5. Test de zoom_ppm (facteur 1, même taille)
    ppm_t* ppm_img2 = ppm_alloc(3, 3, 255);
    // Remplir l'image 3x3 en niveaux de rouge (valeurs 10,20,...,90)
    unsigned char rval = 10;
    for (unsigned int i = 0; i < 3; ++i) {
        for (unsigned int j = 0; j < 3; ++j) {
            ppm_img2->pixels[i][j].r = rval;
            ppm_img2->pixels[i][j].g = 0;
            ppm_img2->pixels[i][j].b = 0;
            rval += 10;
        }
    }
    ppm_t* zoom_img = zoom_ppm(ppm_img2, 1.0, 1, 1, 3, 3);
    if (zoom_img) {
        printf("Zoom facteur 1 PPM: pixel[0][0].r = %d (attendu %d), pixel[2][2].r = %d (attendu %d)\n",
               zoom_img->pixels[0][0].r, ppm_img2->pixels[0][0].r,
               zoom_img->pixels[2][2].r, ppm_img2->pixels[2][2].r);
        ppm_free(&zoom_img);
    } else {
        printf("zoom_ppm a retourné NULL\n");
    }

    // 6. Test de shear_ppm (cx=cy=0 devrait renvoyer la même image)
    ppm_t* shear_img = shear_ppm(ppm_img2, 0.0, 0.0, 3, 3);
    if (shear_img) {
        printf("Shear nul PPM: pixel[1][1].r = %d (attendu %d)\n",
               shear_img->pixels[1][1].r, ppm_img2->pixels[1][1].r);
        ppm_free(&shear_img);
    } else {
        printf("shear_ppm a retourné NULL\n");
    }

    // Nettoyage
    pgm_free(&pgm_img);
    pgm_free(&pgm_img2);
    ppm_free(&ppm_img);
    ppm_free(&ppm_img2);

    printf("[Test Transformations] Fin des tests du module Transformations\n");
    return 0;
}
