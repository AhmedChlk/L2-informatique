#include "ppm.h"
#include "pgm.h"

int main(){
    ppm_t* image = ppm_read_asc("../eye_s_asc.ppm");
    pgm_t* img = NULL;
    ppm_to_pgm(image,&img);
    pgm_write_asc("pgm_from_ppm.pgm",img);
    return 0;
}