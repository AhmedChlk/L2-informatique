#include <stdio.h>
#include <utils.h>

typedef struct{
    int jour;
    int mois;
    int annee;
}une_date_t;

void lire_date(une_date_t* date){
    date->jour = -1;
    date->mois = -1;
    date->annee = -1;
    printf("lecture du jour : \n");
    while(date->jour < 0 || date->jour > 31){
        lire_entier(&date->jour,"entrez le jour :","erreur entrez un jour valide");
        if(date->jour <0 || date->jour > 31)
            printf("entrez un jour valide");
    }
        printf("lecture du mois : \n");
    while(date->mois <0 || date->mois > 12){
        lire_entier(&date->mois,"entrez le mois :","erreur entrez un mois valide");
        if(date->mois <0 || date->mois > 12)
            printf("entrez un mois valide");
    }        
    printf("lecture de l\'annee : \n");       
    lire_entier(&date->annee,"entrez l\'anne :","erreur entrez une annee valide");
}
void perumter (une_date_t* date1 , une_date_t* date2){
    une_date_t temp;
    temp.jour = date1->jour; temp.mois = date1->mois; temp.annee = date1->annee;
    date1->jour = date2->jour; date1->mois = date2->mois; date1->annee = date2->annee;
    date2->jour = temp.jour; date2->mois = temp.mois; date2->annee = temp.annee ;
}

void class_ordre_chrono (une_date_t* tab,int n){
    for(int i=0;i<n;i++){
        for(int j=i+1;j<n;j++){
            if(tab[j].annee == tab[i].annee){
                if(tab[j].mois == tab[i].mois){
                    if(tab[j].jour < tab[i].jour){
                        perumter(&tab[i],&tab[j]);                        
                    }
                }
                else if (tab[j].mois < tab[i].mois){
                    perumter(&tab[i],&tab[j]);                        
                    
                }
            }
            else if (tab[j].annee < tab[i].annee){
                perumter(&tab[i],&tab[j]);                        

            }
        }
    }
    for(int i=0;i<n;i++){
        printf("%d/%d/%d\n",tab[i].jour,tab[i].mois,tab[i].annee);
    }
}
int main(){
    une_date_t tab[3];
    for(int i=0;i<3;i++){
        lire_date(&tab[i]);
    }
    class_ordre_chrono(tab,3);
}