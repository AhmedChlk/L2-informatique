#include<stdio.h>

int main(){
    int value,min,max,compteur=0;
    printf("Entrez les nombres il faut taper CTRL-D pour finir : \n");
    
    while (scanf("%d", &value) != EOF)
    {
        compteur++;
        if(compteur == 1){
            min = value;
            max= value;
        }
        if(value > max){
            max = value;
        }
        if(value < min){
            min = value;
        }
    }
    if(compteur == 0 ){
        printf("vous n\'ave entrer aucune valeur");
    }
    else{
        printf("la minmum est de  %d et le maximun est de  : %d \n",min,max);
    }
    

    
    return 0;
}
