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
    int minocclettre = tab[0].lettre,minocc = tab[0].occ,maxocclettre = tab[0].lettre,maxocc = tab[0].occ ;
    for(int i=1;i<indiceMaxlettre;i++){
        if (tab[i].occ < minocc){
            minocc = tab[i].occ;
            minocclettre = tab[i].lettre;
        }
        if(tab[i].occ > maxocc){
            maxocc=tab[i].occ;
        }
            maxocclettre = tab[i].lettre;
    }
    printf("l'occurence minimal de la chaine : lettre : %c occurence : %d\n",minocclettre,minocc);
    printf("l'occurence maximal de la chaine : lettre : %c occurence : %d\n",maxocclettre,maxocc);
    
    return 0;

    
    
}