#include <stdio.h>
#include <math.h>

//pour s'assurer d'avoir dans tout les cas M_PI 
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

float calculer_perimetre(float rayon) {
    return 2 * M_PI * rayon; 
}

int main() {
    float rayon;
    printf("Entrez le rayon: ");
    while(scanf("%f", &rayon) != 1){
        printf("erreur entrez une valeur valide \n");
        printf("entrez le rayon : ");
        while(getchar() != '\n');

    }
    float perimetre = calculer_perimetre(rayon);
    printf("Le périmètre est: %.2f\n", perimetre);
    return 0;
}
