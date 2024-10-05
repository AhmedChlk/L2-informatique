#include<stdio.h>

int main(){

    int i = 0;
    int longueurChaine = 0 ;
    char mot[100];
    printf("entrez votre chaine de caracteres : ");
    fgets(mot,100,stdin);
    printf("%s",mot);
    while (mot[i+1] != '\0')
    {
        longueurChaine++;
        i++;
    }
    printf("la longueur de la chaine est de : %d",longueurChaine);

    return 0;
}