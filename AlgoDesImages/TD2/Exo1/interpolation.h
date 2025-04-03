// interpolation.h
#ifndef INTERPOLATION_H
#define INTERPOLATION_H

// ordre d'interpolation 
#define N 1 

// Prototypes des fonctions d’interpolation
double B0(double x);
double B1(double x);
double B2(double x);
double B3(double x);

// Déclaration externe du tableau de pointeurs sur fonctions
extern double (*B[4])(double);

// Autres déclarations
// interpolation_pgm(pgm_t *image, double x, double y);

#endif
