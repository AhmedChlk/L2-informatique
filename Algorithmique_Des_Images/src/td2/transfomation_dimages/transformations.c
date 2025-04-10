#include "transformations.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

/* ========================================================================
   Fonctions de base pour les B-splines
   ======================================================================== */

/* Fonction B0 (voisin le plus proche) */
double B0(double x) {
    double absx = fabs(x);
    if (absx < 0.5) return 1.0;
    else if (absx == 0.5) return 0.5;
    else return 0.0;
}

/* Fonction B1 (linéaire) */
double B1(double x) {
    if (fabs(x) > 1.0)
        return 0.0;
    if (x < 0.0)
        return x + 1.0;
    return 1.0 - x;
}

/* Fonction B2 (quadratique) */
double B2(double x) {
    double absx = fabs(x);
    if (absx > 1.5)
        return 0.0;
    if (x <= -0.5)
        return 0.5 * pow(x + 1.5, 2);
    if (x < 0.5)
        return 0.75 - x * x;
    return 0.5 * pow(x - 1.5, 2);
}

/* Fonction B3 (cubique) */
double B3(double x) {
    double absx = fabs(x);
    if (absx > 2.0)
        return 0.0;
    if (absx <= 1.0)
        return 0.5 * pow(absx, 3) - x * x + (2.0 / 3.0);
    return (1.0 / 6.0) * pow(2.0 - absx, 3);
}

/* Tableau de fonctions B */
double (*B[4])(double) = { B0, B1, B2, B3 };

/* ========================================================================
   Fonctions d'interpolation
   ======================================================================== */

/**
 * Fonction utilitaire pour déterminer le rayon du support d'interpolation.
 * Pour B0: support effectif = 0, B1: 1, B2 et B3: on utilise un offset de 2.
 */
static int get_b_spline_support(int n) {
    switch(n) {
        case 0: return 0;
        case 1: return 1;
        case 2: return 2;
        case 3: return 2;
        default: return 2;
    }
}

unsigned char interpolation_pgm(const pgm_t* image, double x, double y) {
    if (image == NULL)
        return 0;
    if (x < 0.0 || y < 0.0 || x >= (double)image->height || y >= (double)image->width)
        return 0;
    
    int offset = get_b_spline_support(N);
    int cx = (int) floor(x);
    int cy = (int) floor(y);
    
    double somme = 0.0;
    double somme_poids = 0.0;
    
    for (int i = cx - offset; i <= cx + offset; i++) {
        if (i < 0 || i >= (int) image->height)
            continue;
        for (int j = cy - offset; j <= cy + offset; j++) {
            if (j < 0 || j >= (int) image->width)
                continue;
            double poids = B[N](x - i) * B[N](y - j);
            somme += poids * image->pixels[i][j];
            somme_poids += poids;
        }
    }
    if (somme_poids > 1e-12)
        somme /= somme_poids;
    
    if (somme < 0.0)
        somme = 0.0;
    if (somme > 255.0)
        somme = 255.0;
    return (unsigned char) round(somme);
}

rgb_t interpolation_ppm(const ppm_t* image, double x, double y) {
    rgb_t couleur = {0, 0, 0};
    if (image == NULL)
        return couleur;
    if (x < 0.0 || y < 0.0 || x >= (double)image->height || y >= (double)image->width)
        return couleur;
    
    int offset = get_b_spline_support(N);
    int cx = (int) floor(x);
    int cy = (int) floor(y);
    
    double somme_r = 0.0, somme_g = 0.0, somme_b = 0.0;
    double somme_poids = 0.0;
    
    for (int i = cx - offset; i <= cx + offset; i++) {
        if (i < 0 || i >= (int) image->height)
            continue;
        for (int j = cy - offset; j <= cy + offset; j++) {
            if (j < 0 || j >= (int) image->width)
                continue;
            double poids = B[N](x - i) * B[N](y - j);
            somme_r += poids * image->pixels[i][j].r;
            somme_g += poids * image->pixels[i][j].g;
            somme_b += poids * image->pixels[i][j].b;
            somme_poids += poids;
        }
    }
    if (somme_poids > 1e-12) {
        somme_r /= somme_poids;
        somme_g /= somme_poids;
        somme_b /= somme_poids;
    }
    if (somme_r < 0.0)
        somme_r = 0.0;
    if (somme_r > image->max_value)
        somme_r = image->max_value;
    if (somme_g < 0.0)
        somme_g = 0.0;
    if (somme_g > image->max_value)
        somme_g = image->max_value;
    if (somme_b < 0.0)
        somme_b = 0.0;
    if (somme_b > image->max_value)
        somme_b = image->max_value;
    
    couleur.r = (unsigned char) round(somme_r);
    couleur.g = (unsigned char) round(somme_g);
    couleur.b = (unsigned char) round(somme_b);
    
    return couleur;
}

/* ========================================================================
   Fonctions de transformations géométriques
   ======================================================================== */

pgm_t* rotation_pgm(const pgm_t* image, double theta, int x0, int y0) {
    if (image == NULL)
        return NULL;
    pgm_t* res = pgm_alloc(image->height, image->width, image->max_value);
    if (res == NULL)
        return NULL;
    
    double cosTheta = cos(theta);
    double sinTheta = sin(theta);
    
    for (unsigned int i = 0; i < res->height; i++) {
        for (unsigned int j = 0; j < res->width; j++) {
            double i_rel = (double)i - x0;
            double j_rel = (double)j - y0;
            double src_x = x0 + cosTheta * i_rel + sinTheta * j_rel;
            double src_y = y0 - sinTheta * i_rel + cosTheta * j_rel;
            res->pixels[i][j] = interpolation_pgm(image, src_x, src_y);
        }
    }
    return res;
}

ppm_t* rotation_ppm(const ppm_t* image, double theta, int x0, int y0) {
    if (image == NULL)
        return NULL;
    ppm_t* res = ppm_alloc(image->height, image->width, image->max_value);
    if (res == NULL)
        return NULL;
    
    double cosTheta = cos(theta);
    double sinTheta = sin(theta);
    
    for (unsigned int i = 0; i < res->height; i++) {
        for (unsigned int j = 0; j < res->width; j++) {
            double i_rel = (double)i - x0;
            double j_rel = (double)j - y0;
            double src_x = x0 + cosTheta * i_rel + sinTheta * j_rel;
            double src_y = y0 - sinTheta * i_rel + cosTheta * j_rel;
            res->pixels[i][j] = interpolation_ppm(image, src_x, src_y);
        }
    }
    return res;
}

ppm_t* zoom_ppm(const ppm_t* image, double lambda, int x0, int y0, unsigned int Dx, unsigned int Dy) {
    if (image == NULL || lambda == 0.0)
        return NULL;
    ppm_t* res = ppm_alloc(Dx, Dy, image->max_value);
    if (res == NULL)
        return NULL;
    
    double cx_out = ((double)Dx - 1.0) / 2.0;
    double cy_out = ((double)Dy - 1.0) / 2.0;
    
    for (unsigned int i = 0; i < Dx; i++) {
        for (unsigned int j = 0; j < Dy; j++) {
            double src_x = x0 + ((double)i - cx_out) / lambda;
            double src_y = y0 + ((double)j - cy_out) / lambda;
            res->pixels[i][j] = interpolation_ppm(image, src_x, src_y);
        }
    }
    return res;
}

ppm_t* shear_ppm(const ppm_t* image, double cx, double cy, unsigned int Dx, unsigned int Dy) {
    if (image == NULL)
        return NULL;
    ppm_t* res = ppm_alloc(Dx, Dy, image->max_value);
    if (res == NULL)
        return NULL;
    
    double denom = 1.0 - cx * cy;
    if (fabs(denom) < 1e-6) {
        // Si transformation non inversible, on copie une partie de l'image
        for (unsigned int i = 0; i < Dx && i < image->height; i++) {
            for (unsigned int j = 0; j < Dy && j < image->width; j++) {
                res->pixels[i][j] = image->pixels[i][j];
            }
        }
        return res;
    }
    for (unsigned int i = 0; i < Dx; i++) {
        for (unsigned int j = 0; j < Dy; j++) {
            double src_x = ((double)i - cx * (double)j) / denom;
            double src_y = (double)j - cy * src_x;
            res->pixels[i][j] = interpolation_ppm(image, src_x, src_y);
        }
    }
    return res;
}
