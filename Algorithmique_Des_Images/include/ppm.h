#ifndef PPM_H
#define PPM_H

#include <stdio.h>
#include "pgm.h"

/* Structure représentant un pixel RGB */
typedef struct {
    unsigned char r, g, b;
} rgb_t;

/* Structure représentant une image PPM */
typedef struct {
    unsigned int height;
    unsigned int width;
    unsigned int max_value;
    rgb_t** pixels;
} ppm_t;

/* -------------------------------------------------------------------------
   Fonction auxiliaire : écriture d'un commentaire dans le fichier
   ------------------------------------------------------------------------- */
/**
 * Écrit un commentaire dans le fichier ouvert.
 * @param f       Pointeur sur le fichier ouvert en écriture.
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
 * @param max_value Valeur maximale d'un canal (typiquement 255).
 * @return Pointeur sur l'image allouée ou NULL en cas d'erreur.
 */
ppm_t* ppm_alloc(unsigned int height, unsigned int width, unsigned int max_value);

/**
 * Libère la mémoire associée à une image PPM.
 * @param img Adresse du pointeur de l'image à libérer (mis à NULL en sortie).
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
 * @param img Pointeur sur l'image PPM (non modifiée).
 */
void ppm_print(const ppm_t* img);

/**
 * Écrit une image PPM au format ASCII (P3) dans un fichier.
 * @param fname   Nom du fichier de destination.
 * @param img     Pointeur sur l'image à écrire.
 * @param comment Commentaire à ajouter dans l'en-tête (optionnel, peut être NULL).
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
 * @param fname   Nom du fichier de destination.
 * @param img     Pointeur sur l'image à écrire.
 * @param comment Commentaire à ajouter dans l'en-tête (optionnel).
 * @return 0 en cas de succès, -1 en cas d'erreur.
 */
int ppm_write_bin(const char* fname, const ppm_t* img, const char* comment);

/* -------------------------------------------------------------------------
   Traitement de l'image : négatif et extraction
   ------------------------------------------------------------------------- */
/**
 * Crée l'image négative de l'image source.
 * @param src Pointeur sur l'image source (non modifiée).
 * @param dst Adresse du pointeur qui recevra l'image négative (doit être NULL ou une image à réutiliser).
 * @return 0 en cas de succès, -1 en cas d'erreur.
 */
int ppm_negative(const ppm_t* src, ppm_t** dst);

/**
 * Extrait une sous-image d'une image PPM et l'enregistre au format ASCII (P3).
 * @param fname      Nom du fichier de destination pour la sous-image.
 * @param image      Pointeur sur l'image source (non modifiée).
 * @param dx         Coordonnée de départ (hauteur) dans l'image source.
 * @param dy         Coordonnée de départ (largeur) dans l'image source.
 * @param sub_height Hauteur de la sous-image à extraire.
 * @param sub_width  Largeur de la sous-image à extraire.
 * @param comment    Commentaire à ajouter dans l'en-tête du fichier extrait (optionnel).
 * @return 0 en cas de succès, -1 en cas d'erreur.
 */
int ppm_extract(const char* fname, const ppm_t* image, int dx, int dy, int sub_height, int sub_width, const char* comment);

/* -------------------------------------------------------------------------
   Histogramme et conversion
   ------------------------------------------------------------------------- */
/**
 * Calcule l'histogramme de chaque composante (R, G, B) de l'image.
 * @param image Pointeur sur l'image source.
 * @return Pointeur sur un tableau de rgb_t de taille (max_value+1) représentant l'histogramme, ou NULL en cas d'erreur.
 */
rgb_t* ppm_get_histogram(const ppm_t* image);

/**
 * Écrit l'histogramme de l'image PPM dans un fichier texte.
 * Le fichier contiendra (max_value+1) lignes avec pour chaque niveau de 0 à max_value le nombre de pixels de chaque composante ayant cette valeur.
 * @param fname Nom du fichier de destination pour l'histogramme.
 * @param image Pointeur sur l'image source.
 * @return 0 en cas de succès, -1 en cas d'erreur.
 */
int ppm_write_histogram(const char* fname, const ppm_t* image);

/**
 * Convertit une image PPM en une image PGM (niveau de gris).
 * @param ppm_img Pointeur sur l'image PPM source.
 * @param pgm_img Adresse du pointeur qui recevra l'image PGM (peut pointer vers NULL ou une image existante à remplacer).
 * @return 0 en cas de succès, -1 en cas d'erreur.
 */
int ppm_to_pgm(const ppm_t* ppm_img, pgm_t** pgm_img);

#endif
