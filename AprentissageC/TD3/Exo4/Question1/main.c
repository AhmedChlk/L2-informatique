#include <stdio.h>
typedef struct{
    char lettre;
    int occ;
    }LettreOcc;

int verificationMiniscule(char* chaine){
    int i=0;
    while(chaine[i] != '\0' && chaine[i] >= 'a' && chaine[i]<= 'z')
        i++;
    return (chaine[i] == '\0' || chaine[i] == '\n');
}

int main(){
    char chaine[255];
    LettreOcc tab[26] ={0};
    int i=0,valide,j,indiceMaxlettre = 0;

    do{
        printf("entrez la chaine de caractere en miniscule : ");
        fgets(chaine,255,stdin);
        valide = verificationMiniscule(chaine);
        if(!valide)
            printf("erreur entrez uniquement des caracteres miniscules \n");

    }while(!valide);
    while(chaine[i] != '\0'){
        if(chaine[i] >= 'a' && chaine[i] <= 'z'){
            
        j = 0;
        while(j<= indiceMaxlettre && !(tab[j].lettre == chaine[i]) ){
            j++;
        }
        if(j>indiceMaxlettre){
            tab[indiceMaxlettre].lettre = chaine[i];
            tab[indiceMaxlettre].occ = 1;
            indiceMaxlettre++;
        }else{
            tab[j].occ += 1;
        }
        }
        i++;
    }
    for(int i=0 ;i<indiceMaxlettre;i++){
        printf("%c : %d \n",tab[i].lettre,tab[i].occ);
    }
    return 0;

    
    
}