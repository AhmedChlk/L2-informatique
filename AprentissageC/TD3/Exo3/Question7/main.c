#include <stdio.h>

void capitalize(char* chaine){
    int i =0;
    while(chaine[i] != '\0'){
        if ((chaine[i] >= 'a' && chaine[i]<= 'z')){
            //chaine[i] -= 32;
            chaine[i] = chaine[i] + ('A' - 'a');
        }
        i++;
    }
}

int main(){
    char chaine[255];
    printf("entrez votre chaine de caractere :");
    fgets(chaine,255,stdin);
    capitalize(chaine);
    printf("la chaine en majuscule : %s",chaine);
    return 0;
}