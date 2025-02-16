#ifndef PGM_H

#define PGM_H

    #include <stdio.h>
    #include <stdlib.h>
    #include <ctype.h>
    #include <string.h>

    typedef struct {
        unsigned int height;
        unsigned int width;
        unsigned int max_value;
        unsigned char **pixels; 
    } pgm_t;

    pgm_t* pgm_alloc(unsigned int height, unsigned int width, unsigned int max_value);

    void pgm_free(pgm_t** image); 

    pgm_t* pgm_read_asc(const char* fname);

    int pgm_write_asc(const char* fname, pgm_t* img);

    pgm_t* pgm_read_bin(const char* fname);

    int pgm_write_bin(const char* fname, pgm_t* img);

    void pgm_negative(pgm_t* src, pgm_t** dest);

    void pgm_extract(const char* fname, pgm_t* image, unsigned int dx, unsigned int dy, unsigned int width, unsigned int height);

    unsigned int* pgm_get_histrogram(pgm_t* image);

    void pgm_write_histogram(const char* fname , pgm_t* image);
#endif