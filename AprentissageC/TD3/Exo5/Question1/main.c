#include <stdio.h>

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
    char chaine[255],chaineCryptee[255],temp;
    int decalement,decalementSave,len,i=0;
    printf("entrez votre chaine de caractere :");
    fgets(chaine,255,stdin);
    len = longueurChaine(chaine);
    if(chaine[len-1]== '\n') 
        chaine[len - 1] = '\0';
    printf("entrez la valeur de decalement : ");
    while(scanf("%d",&decalement) != 1){
        printf("erreur entrez un decalement valide .\n");
        while(getchar() != '\n');
    }
    decalementSave= decalement;
    while(chaine[i]!='\0'){
        decalement= decalementSave;
        if(chaine[i]>= 'a' && chaine[i]<= 'z'){
            temp = chaine[i];
            do{
                temp+= 1;
                if(temp > 'z') temp = 'a';
                decalement--;
            }while(decalement>0);
            chaineCryptee[i] = temp;
        }
        else if(chaine[i]>= 'A' && chaine[i]<= 'Z'){
            temp = chaine[i];
            do{
                temp+= 1;
                if(temp > 'Z') temp = 'A';
                decalement--;
            }while(decalement>0);
            chaineCryptee[i] = temp;
        }
        else{
            chaineCryptee[i] = chaine[i];
        }
        i++;
    }
    printf("%s  devient :  %s \n",chaine,chaineCryptee);
    return 0;
}