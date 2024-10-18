#include <stdio.h>

void dessiner_damier(int t, int c) {
        /*int ligne = 0,tourX=1,changmentdeligne =0;
    for(int i = 0 ; i < t*c; i++){
        if(tourX){
            for(int j =0;j<t;j++){
            if(ligne % 2 == 0)
                for(int k=0;k<c;k++) printf("X");
            else
                for(int k=0;k<c;k++) printf(".");
            ligne ++;
        }
        printf("\n");
        }else{
            for(int j =0;j<t;j++){
            if(ligne % 2 == 0)
                for(int k=0;k<c;k++) printf(".");
            else
                for(int k=0;k<c;k++) printf("X");
            ligne ++;
        }
        printf("\n");
        }
        if(++changmentdeligne == c){
            tourX = !tourX;
            changmentdeligne = 0;
        }
        }
    */

    for (int i = 0; i < t * c; i++) {  // Parcours des lignes du damier
        for (int j = 0; j < t; j++) {  // Parcours des colonnes du damier
            // Alternance des motifs : soit "X", soit "."
            if ((i / c + j) % 2 == 0) {
                for (int k = 0; k < c; k++) {
                    printf("X");
                }
            } else {
                for (int k = 0; k < c; k++) {
                    printf(".");
                }
            }
        }
        printf("\n");
    }
}

int main() {
    dessiner_damier(4, 2);  // Test avec t=4 (nombre de cases), c=2 (taille des cases)
    return 0;
}
