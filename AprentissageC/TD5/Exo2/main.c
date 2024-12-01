#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef enum {
    POSITIF,
    NEGATIF
}signe_t;

typedef struct{
    signe_t signe;
    unsigned int k;
    short* n;   
}nombre_t;
#define BASE_DECIMALE 10
#define BASE_BLOCS 65536

void afficher_decimal(nombre_t nb) {
    int taille_max = nb.k * 5; 
    char* decimal = (char*)malloc(taille_max);
    decimal[0] = '0'; 
    for (int i = nb.k - 1; i >= 0; i--) {
        int carry = nb.n[i];
        int taille = strlen(decimal);

        // Multiplier le résultat intermédiaire par la base des blocs (65536)
        for (int j = 0; j < taille; j++) {
            int digit = (decimal[j] - '0') * BASE_BLOCS + carry;
            decimal[j] = (digit % BASE_DECIMALE) + '0'; // Stocker le reste
            carry = digit / BASE_DECIMALE;             // Retenue pour le chiffre suivant
        }

        // Si retenue restante, l'ajouter au résultat
        while (carry > 0) {
            decimal[taille++] = (carry % BASE_DECIMALE) + '0';
            carry /= BASE_DECIMALE;
        }
    }

    // Ajout du signe si nécessaire
    if (nb.signe == NEGATIF) {
        printf("-");
    }

    // Affichage du résultat en inversant l'ordre des chiffres
    for (int i = strlen(decimal) - 1; i >= 0; i--) {
        printf("%c", decimal[i]);
    }
    printf("\n");

    free(decimal);
}

nombre_t cree_nombre( unsigned int p){
    int nb_short = (p + 15 )/16;
    nombre_t nb ;
    nb.signe = POSITIF;
    nb.k = nb_short;
    nb.n = (short*) malloc(nb_short * sizeof(short));
    for(int i=0;i<nb_short;i++){
        nb.n[i] = 0;
    }
    return nb;
}
void liberer_nombre (nombre_t* nb){
    free(nb->n);
    nb->n= NULL;
    nb->k = 0;

}
int min (int n1,int n2){
    return (n1 < n2) ? n1 : n2;
}
int max (int n1,int n2){
   return (n1 > n2) ? n1 : n2;
}
void add_sub (nombre_t n1 , nombre_t n2 , nombre_t* res,int op){
    int retenu = 0;
    int max_k = max(n1.k,n2.k);
    nombre_t n3 = cree_nombre (16 *max_k);
    switch(op){
        case 1 : //Addition
            if(n1.signe == n2.signe){
                
                for(int i=0;i< max_k;i++){
                    short val1 = (i < n1.k) ? n1.n[i] : 0; 
                    short val2 = (i < n2.k) ? n2.n[i] : 0;
                    n3.n[i] = val1 + val2 + retenu ; 
                    retenu = (n3.n[i] < val1 || n3.n[i] < val2) ? 1 : 0 ;
                }
                if (retenu){
                    n3.k++;
                    n3.n = (short*) realloc (n3.n,n3.k * sizeof(short));
                    n3.n[n3.k] = 1;
                }                    
            
            n3.signe = n2.signe;
            }
            else {
                if (n1.signe == NEGATIF){
                    n1.signe = POSITIF;
                    add_sub(n1,n2,res,2);
                }
                else{
                    n2.signe = POSITIF;
                    add_sub(n1,n2,res,2);
                }
                return;
            }   
            break;

        case 2 : // soustraction
            for(int i=0;i< max_k;i++){
                    short val1 = (i < n1.k) ? n1.n[i] : 0; 
                    short val2 = (i < n2.k) ? n2.n[i] : 0;
                    n3.n[i] = val1 - val2 - retenu ; 
                    if (n3.n[i] < 0 ){
                        n3.n[i] = (n3.n[i] + 65536) %65536;
                        retenu = 1;
                    }
                    else{
                        retenu = 0;
                    }
            }
            if(retenu)
            n3.signe = NEGATIF;
            else
                n3.signe = POSITIF;
            break;
    }


    res->signe = n3.signe;
    res->n = (short*) realloc(res->n,n3.k * sizeof(short));
    res->k = n3.k;
    for(int i=0;i<res->k;i++){
        res->n[i] = n3.n[i];
    }
    liberer_nombre(&n3);
}

void mult(nombre_t n1, nombre_t n2, nombre_t* res) {
    // Taille maximale possible du résultat
    int max_k = n1.k + n2.k; 
    nombre_t n3 = cree_nombre(16 * max_k);

    // Initialisation des blocs
    for (int i = 0; i < n3.k; i++) {
        n3.n[i] = 0;
    }

    // Multiplication bloc par bloc
    for (int i = 0; i < n1.k; i++) {
        int retenu = 0;
        for (int j = 0; j < n2.k; j++) {
            int index = i + j;

            // Calcul du produit et ajout de la retenue
            long produit = (long)n1.n[i] * n2.n[j] + n3.n[index] + retenu; 

            // Mise à jour du bloc courant
            n3.n[index] = produit % 65536; // Partie basse
            retenu = produit / 65536;     // Retenue pour le bloc suivant
        }

        // Ajouter la retenue restante
        if (retenu > 0) {
            int index_retenu = i + n2.k;
            if (index_retenu >= n3.k) { 
                // Étendre la taille de n3 si nécessaire
                n3.k++;
                n3.n = (short*) realloc(n3.n, n3.k * sizeof(short));
                n3.n[n3.k - 1] = 0; // Initialiser le nouveau bloc
            }
            n3.n[index_retenu] += retenu;
        }
    }

    while (n3.k > 1 && n3.n[n3.k - 1] == 0) {
    }

    res->signe = (n1.signe == n2.signe) ? POSITIF : NEGATIF;
    res->n = (short*) realloc(res->n, n3.k * sizeof(short));
    res->k = n3.k;
    for (int i = 0; i < res->k; i++) {
        res->n[i] = n3.n[i];
    }

    liberer_nombre(&n3);
}


void affichage_binaire(short n)
{
    int i;
    for (i = 15; i >= 0; i--)
        printf("%d", (n >> i ) & 1);
    printf(" ");
} 
void affichage_hexa(short n)
{
    printf("%4x",n);
}
void afficher_nbr (nombre_t nb){
    printf("--------------------affichage nombre--------------------\n");
    switch(nb.signe){
        case POSITIF :
            printf("+ ");
            break;
        case NEGATIF :
            printf("- ");
            break;
    }
    for(int i=nb.k-1;i>=0;i--){
        affichage_binaire(nb.n[i]);
        //affichage_hexa(nb.n[i]);
    }
    printf("\n--------------------fin affichage-----------------------\n");

}

int main(){
    nombre_t n = cree_nombre(48);
    n.n[0] = 1;
    n.n[1] = 2;
    n.n[2] = 3;
    afficher_decimal(n);
    return 0;
}