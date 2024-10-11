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
    char chaine[255];//chaineCryptee[255]//,temp,decalementSave;
    int decalement,len,i=0;
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
    //decalementSave= decalement;
    while(chaine[i]!='\0'){
        /*decalement= decalementSave;
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
        }*/
/*
        if(chaine[i]>= 'a' && chaine[i]<= 'z')
              chaine[i] =(chaine[i] - 'a' + decalement ) % ('z'-'a'+1) + 'a';
        else if(chaine[i]>= 'A' && chaine[i]<= 'Z')
            chaine[i] =(chaine[i] - 'A' + decalement ) % ('Z'-'A'+1) + 'A';
*/
        char KA,KZ;
        if(chaine[i]>= 'a' && chaine[i]<= 'z')
            {KA = 'a'; KZ='z';}
            //  chaine[i] =(chaine[i] - 'a' + decalement ) % ('z'-'a'+1) + 'a';
        else if(chaine[i]>= 'A' && chaine[i]<= 'Z')
            {KA = 'A'; KZ='Z';}
            //chaine[i] =(chaine[i] - 'A' + decalement ) % ('Z'-'A'+1) + 'A';
        chaine[i] =(chaine[i] - KA + decalement ) % (KZ-KA+1) + KA;
        
        i++;
    }
    printf("chaine cryptee : %s \n",chaine);
    return 0;
}