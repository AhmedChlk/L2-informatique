#ifndef PPM_H
#define PPM_H
#include <stdio.h>
#include "pgm.h"

    typedef struct {
        unsigned char r,g,b;
    }rgb_t;

    typedef struct{
        unsigned int height,width,max_value;
        rgb_t** pixels;
    }ppm_t;

/* -------------------------------------------------------------------------
   Fonction auxiliaire : écriture d'un commentaire dans le fichier
   ------------------------------------------------------------------------- */
/**
 * Écrit un commentaire dans le fichier ouvert.
 * @param f        Pointeur sur le fichier ouvert en écriture.
 * @param comment Chaîne de caractères contenant le commentaire (optionnel).
 * @return 0 en cas de succès, -1 en cas d'erreur.
 */
int write_comment(FILE* f, const char* comment);

/* -------------------------------------------------------------------------
   Allocation et libération de l'image PPM
   ------------------------------------------------------------------------- */
/**
 * Alloue et initialise une image PPM.
 * Les pixels sont initialisés à la valeur maximale (blanc).
 * @param height    Hauteur de l'image.
 * @param width     Largeur de l'image.
 * @param max_value Valeur maximale d'un canal.
 * @return Pointeur sur l'image allouée ou NULL en cas d'erreur.
 */
ppm_t* ppm_alloc(unsigned int height, unsigned int width, unsigned int max_value);
/**
 * Libère la mémoire associée à une image PPM.
 * @param img Pointeur sur le pointeur de l'image à libérer.
 */
void ppm_free(ppm_t** img);
/* -------------------------------------------------------------------------
   Lecture et écriture en format ASCII (P3)
   ------------------------------------------------------------------------- */
/**
 * Lit une image PPM au format ASCII (P3) depuis un fichier.
 * @param fname Nom du fichier à lire.
 * @return Pointeur sur l'image lue ou NULL en cas d'erreur.
 */
ppm_t* ppm_read_asc(const char* fname);

/**
 * Affiche les informations de l'image PPM sur la sortie standard.
 * @param img Pointeur sur l'image (non modifiée).
 */
void ppm_print(const ppm_t* img);

/**
 * Écrit une image PPM au format ASCII (P3) dans un fichier.
 * @param fname    Nom du fichier de destination.
 * @param img      Pointeur sur l'image à écrire.
 * @param comment  Commentaire à ajouter dans l'en-tête (optionnel).
 * @return 0 en cas de succès, -1 en cas d'erreur.
 */
int ppm_write_asc(const char* fname, const ppm_t* img, const char* comment);

/* -------------------------------------------------------------------------
   Lecture et écriture en format binaire (P6)
   ------------------------------------------------------------------------- */
/**
 * Lit une image PPM au format binaire (P6) depuis un fichier.
 * @param fname Nom du fichier à lire.
 * @return Pointeur sur l'image lue ou NULL en cas d'erreur.
 */
ppm_t* ppm_read_bin(const char* fname);
/**
 * Écrit une image PPM au format binaire (P6) dans un fichier.
 * @param fname    Nom du fichier de destination.
 * @param img      Pointeur sur l'image à écrire.
 * @param comment  Commentaire à ajouter dans l'en-tête (optionnel).
 * @return 0 en cas de succès, -1 en cas d'erreur.
 */
int ppm_write_bin(const char* fname, const ppm_t* img, const char* comment);



/* -------------------------------------------------------------------------
   Traitement de l'image : négatif et extraction
   ------------------------------------------------------------------------- */
/**
 * Crée l'image négative de l'image source.
 * @param src Pointeur sur l'image source (constante).
 * @param dst Adresse d'un pointeur qui recevra l'image négative.
 * @return 0 en cas de succès, -1 en cas d'erreur.
 */
int ppm_negative(const ppm_t* src, ppm_t** dst);


/**
 * Extrait une sous-image d'une image PPM et l'enregistre au format ASCII (P3).
 * @param fname       Nom du fichier de destination.
 * @param image       Pointeur sur l'image source (non modifiée).
 * @param dx          Coordonnée verticale de départ dans l'image source.
 * @param dy          Coordonnée horizontale de départ dans l'image source.
 * @param sub_height  Hauteur de la sous-image.
 * @param sub_width   Largeur de la sous-image.
 * @param comment     Commentaire à ajouter dans l'en-tête du fichier extrait (optionnel).
 * @return 0 en cas de succès, -1 en cas d'erreur.
 */
int ppm_extract(const char* fname, const ppm_t* image, int dx, int dy, int sub_height, int sub_width, const char* comment);


/**
 * recupere l'histogram de Chaque Composante (r,g,b) de l'image
 * @param image       Pointeur sur l'image.
 * @return  pointeur sur un tableau de rgb_t
 */
rgb_t* ppm_get_histogram(const ppm_t* image);


int ppm_write_histogram(const char* fname,const ppm_t* image);

int ppm_to_pgm(ppm_t* ppm_img,pgm_t** pgm_img);

#endif