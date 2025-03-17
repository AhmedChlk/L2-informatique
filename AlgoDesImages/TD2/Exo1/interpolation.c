#include <stdlib.h>
#include <math.h>
#include "interpolation.h"

double B0(double x){
    if(labs(x) > 0.5)
        return 0;
    else if (labs(x) < 0.5)
        return 1;
    else 
        return 0.5;
}


double B1(double x){
    if(labs(x) > 1)
        return 0;
    else if ( x >= -1 && x <= 0)
        return x +1;
    else
        return 1-x;
}


double B2(double x){
    if(labs(x) > 1.5)
        return 0;
    else if (x >= -1.5 && x <= -0.5)
        return 0.5*pow(x+1.4,2);
    else if (x >=-0.5 && x <= 0.5)
        return 0.75 - pow(x,2);
    else 
        return 0.5 * pow(x-1.5,2);
}


double B3(double x){
    if(labs(x)>2)
        return 0;
    else if ( x >= 0 && x <= 1)
        return (0.5*pow(labs(x),3)) - pow(x,2) + (2.0/3.0);
    else 
        return 1/6 * (2 - pow(labs(x),3));
}

unsigned char interpolation_pgm(pgm_t *image, double x, double y){
    
}