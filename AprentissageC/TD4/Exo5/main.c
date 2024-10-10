#include <stdio.h>


void dessiner_damier(int t,int c )
{
    int tourX;   
    for(int i = 0 ; i < t*c; i++){
        if(i % 2 == 0)
            tourX = 1;
        else
            tourX = 0;
        for(int j=0;j<t;j++){
            if(tourX){
                for(int k=0;k<c;k++){
                    printf("X");
                }
                tourX = !(tourX);
            }else{
                 for(int k=0;k<c;k++){
                    printf(".");
                }
                tourX = !(tourX);
            }
        }
        printf("\n");
    }
}
int main(){
    dessiner_damier(4,2);
    return 0;
}