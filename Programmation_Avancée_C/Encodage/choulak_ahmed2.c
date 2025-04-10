#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct {
    char tab_64[64];
}paquet_t;

void lecture_message(const char* nom_fichier) {
    FILE* F = fopen(nom_fichier, "rb");
    if (F == NULL) {
        printf("Erreur : Impossible d'ouvrir le fichier %s\n", nom_fichier);
        return;
    }

    char message[65];
    size_t bytes_read;

    while ((bytes_read = fread(message, sizeof(char), 64, F)) > 0) {
        message[bytes_read] = '\0';
        printf("%s", message);
    }

    fclose(F); // Fermeture du fichier
}


unsigned char decode_special (unsigned char c ){
    switch(c){
        case 16: return 10;
        case 17: return 32;
        case 18: return 39;
        case 19: return 40;
        case 20: return 41;
        case 21: return 42;
        case 22: return 43;
        case 23: return 44;
        case 24: return 45;
        case 25: return 46;
        case 26: return 58;
        case 27: return 59;
        case 28: return 61;
        case 29: return 62;
        case 30: return 63;
        case 31: return 95;
        default : return c;
    }
}
void analyse(paquet_t paquet, int tab_frequence[256]){
    for(int i=0;i<64;i++){
        unsigned char c = paquet.tab_64[i];
        c = decode_special(c);
        tab_frequence[c]++;
    }
}

paquet_t* cree_tab_paquet(const char* nom_fichier, int* nb_paquets) {
    paquet_t* p = (paquet_t*) malloc(1 * sizeof(paquet_t));
    int cpt = 0;
    FILE* F = fopen(nom_fichier, "rb");
    if (F == NULL) {
        printf("Erreur : Impossible d'ouvrir le fichier %s\n", nom_fichier);
        exit(1);
    }
    size_t bytes_read;

    while ((bytes_read = fread(p[cpt].tab_64, sizeof(char), 64, F)) > 0) {
        cpt++;
        p = (paquet_t*) realloc(p, (cpt + 1) * sizeof(paquet_t)); // Réallocation pour un nouveau paquet
    }

    fclose(F);
    *nb_paquets = cpt; // Retourner le nombre de paquets via un pointeur
    return p;
}

void init_tab_frequence(int* tab){
    for(int i=0;i<256;i++){
        tab[i] = 0;
    }
}
int determiner_cle( paquet_t* tab_paq,int nbr_paquets){
    int tab_frequence[256];
    init_tab_frequence(tab_frequence);
    for(int i=0;i<nbr_paquets;i++){
        analyse(tab_paq[i],tab_frequence);
    }
    int maxfrequence = tab_frequence[0];
    int indice = 0;
    for(int i=1;i<256;i++){
        if(tab_frequence[i]> maxfrequence){
            maxfrequence = tab_frequence[i];
            indice = i;
        }

    }
        return (indice - 'e' + 26 ) % 26 ;

}
int main(){
    //lecture_message("message.bin");
    int n;
    paquet_t* p = cree_tab_paquet("exemple.bin",&n);
    printf("%d\n",determiner_cle(p,n));

    return 0;
}