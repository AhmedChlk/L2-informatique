#include<stdio.h>

int longueurChaine (char* chaine){
    int i=0,longueurCh=0;
    while (chaine[i+1] != '\0')
    {
        longueurCh++;
        i++;
    }
    return longueurCh;
}

int main(){    

    char mot[100],temp;
    printf("entrez votre chaine de caracteres : ");
    fgets(mot,100,stdin);
    int longueurMot;
    longueurMot = longueurChaine(mot);
    int j= longueurMot;
    
        for(int i=0 ; i < longueurMot/2 +1;i++)
    {   
        temp = mot[i];
        mot[i] = mot[j];
        mot[j]=temp;
        j--;
    }
    printf("la chaine inversée est : %s",mot);

    return 0;
}