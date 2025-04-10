#include <stdio.h>

int main (){
    int n;
    printf("Entrez votre nombre  : ");
    while (scanf("%d",&n) != 1)
    {
        printf("Erreur entrez une valeur valid \n");
        printf("Entrez votre nombre : ");
        while (getchar() != '\n');
    }
    int compteur = 0,nombre;
    while (n >0){
        nombre = n%10;
        n /= 10 ;
        if (nombre> 0) compteur ++;
    }
    printf("le nombre de chiffres non nuls dans son ecriture decimal est de : %d\n ", compteur);

}