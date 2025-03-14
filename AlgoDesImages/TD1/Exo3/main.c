#include<stdio.h>
#include"jpeg.h"
int main(){
    pgm_t* img = pgm_read_asc("eye_s_asc.pgm");
    printf("Compression en jpeg\n");
    pgm_to_jpeg(img,"eye_s.txt");
    printf("la taille en png : %d , la taille en jpeg : %d . le ration : %f\n",fsize("eye_s_asc.pgm"),fsize("eye_s.txt"),(float)fsize("eye_s.txt")/fsize("eye_s_asc.pgm"));
    return 0;
}