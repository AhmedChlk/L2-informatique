#include<stdio.h>

int main(){

 int nombreLettres = 0,nombreNombres=0;
    
    int i = 0;
    char mot[100];
    printf("entrez votre chaine de caracteres : ");
    fgets(mot,100,stdin);
    while (mot[i] != '\0')
    {
        if ((mot[i]>= 'a' && mot[i] <= 'z') || (mot[i]>= 'A' && mot[i] <= 'Z')) nombreLettres++;
        if (mot[i] >= '0' && mot[i] <= '9') nombreNombres++;
        i++;
    }
    printf("le nombre de lettres est de : %d le nombre de nombres est de %d",nombreLettres,nombreNombres);

    return 0;
}