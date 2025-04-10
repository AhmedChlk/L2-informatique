#ifndef TRANSFORMATIONS_H
#define TRANSFORMATIONS_H

#include <math.h>
#include "pgm.h"
#include "ppm.h"

/* 
 * Définition de l'ordre d'interpolation.
 * Par défaut, nous utilisons N = 1 pour l'interpolation bilinéaire.
 */
#ifndef N
#define N 1
#endif

/* Fonctions de base pour l'interpolation par B-spline.
 * Ces fonctions renvoient le poids associé à une distance donnée.
 */
double B0(double x);
double B1(double x);
double B2(double x);
double B3(double x);

/* Tableau de pointeurs sur fonctions pour accéder à la fonction B correspondante.
 * Par exemple, B[N](x) renvoie la valeur de la fonction Bₙ en x.
 */
extern double (*B[4])(double);

/**
 * Interpole la valeur d'un pixel en niveaux de gris (PGM) pour des coordonnées réelles (x,y)
 * en utilisant l'interpolation par B-spline d'ordre N.
 * La formule appliquée est :
 *   f(x, y) = Σ₍i,j₎ B[N](x - i) · B[N](y - j) · f(i,j)
 *
 * @param image Pointeur sur l'image PGM source.
 * @param x     Coordonnée réelle x.
 * @param y     Coordonnée réelle y.
 * @return Valeur interpolée (unsigned char) comprise entre 0 et 255.
 */
unsigned char interpolation_pgm(const pgm_t* image, double x, double y);

/**
 * Interpole la valeur d'un pixel couleur (PPM) pour des coordonnées réelles (x,y)
 * en utilisant l'interpolation par B-spline d'ordre N.
 * Chaque composante (R, G, B) est interpolée selon la même formule.
 *
 * @param image Pointeur sur l'image PPM source.
 * @param x     Coordonnée réelle x.
 * @param y     Coordonnée réelle y.
 * @return Une structure rgb_t contenant la couleur interpolée.
 */
rgb_t interpolation_ppm(const ppm_t* image, double x, double y);

/**
 * Effectue une rotation d'une image PGM d'un angle theta (en radians) autour du point (x0,y0).
 * L'image résultante possède la même taille que l'image source.
 *
 * @param image Pointeur sur l'image PGM source.
 * @param theta Angle de rotation en radians.
 * @param x0    Coordonnée x du centre de rotation.
 * @param y0    Coordonnée y du centre de rotation.
 * @return Nouvelle image PGM après rotation (à libérer avec pgm_free).
 */
pgm_t* rotation_pgm(const pgm_t* image, double theta, int x0, int y0);

/**
 * Effectue une rotation d'une image PPM d'un angle theta (en radians) autour du point (x0,y0).
 * L'image résultante possède la même taille que l'image source.
 *
 * @param image Pointeur sur l'image PPM source.
 * @param theta Angle de rotation en radians.
 * @param x0    Coordonnée x du centre de rotation.
 * @param y0    Coordonnée y du centre de rotation.
 * @return Nouvelle image PPM après rotation (à libérer avec ppm_free).
 */
ppm_t* rotation_ppm(const ppm_t* image, double theta, int x0, int y0);

/**
 * Applique un zoom sur une image PPM autour du point (x0,y0) en utilisant le facteur lambda.
 * La taille de l'image résultante est spécifiée par Dx (hauteur) et Dy (largeur).
 *
 * @param image Pointeur sur l'image PPM source.
 * @param lambda Facteur de zoom (lambda > 1 pour agrandir, < 1 pour réduire).
 * @param x0    Coordonnée x du centre du zoom.
 * @param y0    Coordonnée y du centre du zoom.
 * @param Dx    Hauteur de l'image résultante.
 * @param Dy    Largeur de l'image résultante.
 * @return Nouvelle image PPM après zoom (à libérer avec ppm_free).
 */
ppm_t* zoom_ppm(const ppm_t* image, double lambda, int x0, int y0, unsigned int Dx, unsigned int Dy);

/**
 * Applique une transformation par cisaillement (shear) sur une image PPM.
 * Les facteurs cx et cy définissent respectivement l'étirement horizontal et vertical.
 * La taille de l'image résultante est spécifiée par Dx et Dy.
 *
 * @param image Pointeur sur l'image PPM source.
 * @param cx    Facteur de cisaillement horizontal.
 * @param cy    Facteur de cisaillement vertical.
 * @param Dx    Hauteur de l'image résultante.
 * @param Dy    Largeur de l'image résultante.
 * @return Nouvelle image PPM après cisaillement (à libérer avec ppm_free).
 */
ppm_t* shear_ppm(const ppm_t* image, double cx, double cy, unsigned int Dx, unsigned int Dy);

#endif
