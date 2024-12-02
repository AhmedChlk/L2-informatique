#include<stdio.h>

int nombre_ackerman (int m ,int n){
    if(m == 0)
        return n + 1;
    else if (m > 0 && n == 0)
        return nombre_ackerman(m-1,1);
    else 
        return nombre_ackerman(m-1,nombre_ackerman(m,n-1)); 
}

int main(){
    printf("%d",nombre_ackerman(3,3));
    return 0;
}