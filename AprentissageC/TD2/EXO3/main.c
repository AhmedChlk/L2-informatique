#include <stdio.h>

int main(){
    printf("Entrez les nombres pour la moyenne il faut taper CTRL-D pour finir");
    int value , compteur = 0,somme = 0;
    while (scanf("%d", &value) != EOF)
    {
       compteur++;
       somme += value;
    }
    printf("la moyenne est de  %d", somme / compteur);

    
}