#include <stdio.h>
#include <math.h>

double distance_points(double xa, double ya, double xb, double yb) {
    return sqrt(((xb - xa) * (xb - xa)) + ((yb - ya) * (yb - ya)));
}

int main() {
    double xa, ya, xb, yb, distance;

    printf("Entrez les coordonnées du point A (xa ya) : ");
    while (scanf("%lf %lf", &xa, &ya) != 2) {
        printf("Entrez des coordonnées valides : ");
        while (getchar() != '\n');
    }

    printf("Entrez les coordonnées du point B (xb yb) : ");
    while (scanf("%lf %lf", &xb, &yb) != 2) {
        printf("Entrez des coordonnées valides : ");
        while (getchar() != '\n');
    }

    distance = distance_points(xa, ya, xb, yb);
    printf("La distance est de : %lf\n", distance);
    
    return 0;
}
