#include <stdio.h>

void calculer_moutons_et_dindons(int t, int p) {
    int m = (p - 2 * t) / 2;
    
    if ((p - 2 * t) % 2 == 0 && m >= 0 && m <= t) {
        int d = t - m;
        printf("Il y a %d moutons et %d dindons.\n", m, d);
    } else {
        printf("Aucune combinaison valide de moutons et de dindons pour t = %d et p = %d.\n", t, p);
    }
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
