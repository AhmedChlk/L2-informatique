#include <stdio.h>

void calculer_moutons_dindons(int t, int p) {
    int m, d;
    
    for (m = 0; m < t; m++) {
        d = t - m;
        
        if (4 * m + 2 * d == p) {
            printf("Nombre de moutons: %d\n", m);
            printf("Nombre de dindons: %d\n", d);
            return;
        }
    }
    
    printf("Il n'est pas possible d'avoir %d têtes et %d pattes.\n", t, p);
}

int main() {
    int t, p;
    
    printf("Entrez le nombre de têtes: ");
    scanf("%d", &t);
    printf("Entrez le nombre de pattes: ");
    scanf("%d", &p);
    calculer_moutons_dindons(t, p);
    
    return 0;
}
