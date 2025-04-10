#include<stdio.h>
int tailleChaine (char* chaine){
    int longueurChaine,i=0;
    while(chaine[i+1] != '\0'){
        longueurChaine++;
        i++;
    }
    return longueurChaine;
}


int main(){
    char chaine1[255],chaine2[255];
    int resultat=-2,i=0;
    printf("entrez votre premier chaine de caractere :");
    fgets(chaine1,255,stdin);
    printf("entrez votre deuxieme chaine de caractere : ");
    fgets(chaine2,255,stdin);
    while((chaine1[i]!= '\0' || chaine2[i]!= '\0') && chaine1[i] == chaine2[i]){
        i++;
    }
    if(chaine1[i] == '\0' && chaine2[i] == '\0') resultat = 0;
    else if (chaine1[i] == '\0' || chaine2[i]> chaine1[i]) resultat = -1;
    else if (chaine2[i]== '\0' || chaine1[i]> chaine2[i]) resultat = 1;

    switch(resultat){
        case 1:
            printf("haine1 > chaine 2");
            break;
        case -1:
            printf("chaine 2 > chaine 1 ");
            break;
        case 0:
            printf("chaine1 = chaine2");
            break;
        default:
            printf("erreur");
    }
}



