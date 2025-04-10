#ifndef PGM_H
#define PGM_H

#include <stdio.h>

// Structure représentant une image en niveaux de gris (PGM)
typedef struct {
    unsigned int height;
    unsigned int width;
    unsigned int max_value;
    unsigned char **pixels;
} pgm_t;

/**
 * Alloue une nouvelle image PGM de dimensions données.
 * Les pixels sont initialisés à la valeur maximale (blanc).
 * @param height Hauteur de l'image.
 * @param width  Largeur de l'image.
 * @param max_value Valeur maximale des pixels (ex: 255).
 * @return Pointeur sur l'image allouée, ou NULL si échec.
 */
pgm_t* pgm_alloc(unsigned int height, unsigned int width, unsigned int max_value);

/**
 * Libère la mémoire d'une image PGM.
 * @param image Adresse du pointeur de l'image à libérer (celui-ci sera mis à NULL).
 */
void pgm_free(pgm_t** image);

/**
 * Lit une image PGM depuis un fichier au format ASCII (P2).
 * @param fname Chemin du fichier PGM à lire.
 * @return Pointeur sur l'image lue, ou NULL en cas d'erreur.
 */
pgm_t* pgm_read_asc(const char* fname);

/**
 * Écrit une image PGM dans un fichier au format ASCII (P2).
 * @param fname Chemin du fichier de sortie.
 * @param img   Pointeur sur l'image PGM à écrire.
 * @return 0 si succès, -1 en cas d'erreur.
 */
int pgm_write_asc(const char* fname, const pgm_t* img);

/**
 * Lit une image PGM depuis un fichier au format binaire (P5).
 * @param fname Chemin du fichier PGM (binaire) à lire.
 * @return Pointeur sur l'image lue, ou NULL en cas d'erreur.
 */
pgm_t* pgm_read_bin(const char* fname);

/**
 * Écrit une image PGM dans un fichier au format binaire (P5).
 * @param fname Chemin du fichier de sortie.
 * @param img   Pointeur sur l'image PGM à écrire.
 * @return 0 si succès, -1 en cas d'erreur.
 */
int pgm_write_bin(const char* fname, const pgm_t* img);

/**
 * Calcule le négatif d'une image PGM source.
 * @param src  Pointeur sur l'image source.
 * @param dest Adresse du pointeur qui recevra l'image négative (nouvelle image allouée).
 * @return 0 si succès, -1 en cas d'erreur.
 */
int pgm_negative(const pgm_t* src, pgm_t** dest);

/**
 * Extrait une sous-image d'une image PGM et l'enregistre dans un fichier (format ASCII).
 * @param fname Nom du fichier de destination pour la sous-image.
 * @param image Image source.
 * @param dx, dy Coordonnées de départ (haut-gauche) de la zone à extraire.
 * @param sub_height Hauteur de la sous-image à extraire.
 * @param sub_width  Largeur de la sous-image à extraire.
 * @return 0 si succès, -1 si paramètres invalides ou erreur d'écriture.
 */
int pgm_extract(const char* fname, const pgm_t* image, unsigned int dx, unsigned int dy, unsigned int sub_height, unsigned int sub_width);

/**
 * Calcule l'histogramme des niveaux de gris d'une image PGM.
 * @param image Image source.
 * @return Tableau de taille (max_value+1) contenant la fréquence de chaque niveau (0 à max_value). NULL en cas d'erreur.
 */
unsigned int* pgm_get_histogram(const pgm_t* image);

/**
 * Écrit l'histogramme d'une image PGM dans un fichier texte.
 * @param fname Nom du fichier de sortie pour l'histogramme.
 * @param image Image source.
 * @return 0 si succès, -1 en cas d'erreur.
 */
int pgm_write_histogram(const char* fname, const pgm_t* image);

#endif
