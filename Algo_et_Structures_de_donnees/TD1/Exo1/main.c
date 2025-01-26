//representation a l'aide du tableau de papa
#include <stdio.h>

void trouver_feuilles (int* Arbre ,int* feuilles ,int n){
    int nf = 0;
    for(int i=0;i<n;i++){
        int occ = 0;
        for(int j=0;j<n;j++){
            if(Arbre[j] == i)
                occ++;
        }
        if(occ == 0){
            feuilles[nf] = i;
            nf++;
        }
    }
printf("\n");
}

int monter_arbre(int* Arbre,int f){
    //retourner la hauteur depuis une feuille 
    int h=0;
    while(Arbre[f] != -1){
        f = Arbre[f];
        h++;
    }
    return h;
}
int nombre_feuilles(int* Arbre , int n){
    int nb_feuilles = 0 ;
    for(int i=0;i<n;i++){
        int occ = 0;
        for(int j=0;j<n;j++){
            if(Arbre[j] == i)
                occ++;
        }
        if(occ == 0){
            nb_feuilles++;
        }
    }
    return nb_feuilles;
}

void trouver_hauteur(int* Arbre,int n){
    int max_hauteur = 0;
    for(int i=0;i<n;i++){
        int h = 0;
        int val = Arbre[i];
        while(val != -1){
            h++;
            val = Arbre[val];
        }
        if(h > max_hauteur)
            max_hauteur = h;
    }
    printf("la hauteur de l'arbre est : %d\n",max_hauteur);

}

int main(void){
    int n;
    printf("entrez nombre de noeuds de votre arbre ");
    while (scanf("%d",&n) != 1 && n <= 1)
    {
        printf("erreur entrez un nombre de noeuds valide\n");
        while(getchar() != '\n'); 
    }
    int Arbre[n];
    int feuilles[n];
    Arbre[0] = -1;
    for(int i=1;i<n;i++){
        printf("entrez le pere de %d\n",i);
        while (scanf("%d",&Arbre[i]) != 1 && n < 0)
        {
        printf("erreur entrez un pere valide\n");
        while(getchar() != '\n'); 
        }
    }
    trouver_feuilles(Arbre,feuilles,n);
    printf("les feuilles sont: ");
    for(int i=0;i<nombre_feuilles(Arbre,n);i++){
        printf("%d ",feuilles[i]);
    }
    printf("\n");
    printf("la hauteur de chaque feuille : ");
        for(int i=0;i<nombre_feuilles(Arbre,n);i++){
        printf("%d ",monter_arbre(Arbre,feuilles[i]));
    }
    printf("\n");
    trouver_hauteur(Arbre,n);

    
    return 0;
}