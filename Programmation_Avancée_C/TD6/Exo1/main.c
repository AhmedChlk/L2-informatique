#include<stdio.h>

int addition(int a, int b){
    if (b == 0)
        return a;
    if(b < 0)
        return -1 + addition(a,++b);
    else
        return 1 + addition(a,--b);
}
int soustraction(int a,int b){
    if(b == 0)
        return a;
    if(b < 0)
        return 1 +  soustraction(a,++b);
    else
        return -1 + soustraction(a,++b); 
    }
int multiplication(int a,int b){
    if(a == 0)
        return 0;
    else
        return addition(b,0) + multiplication(--a,b);
}
int main(){
    printf("%d \n",addition(1,2));
    printf("%d \n",soustraction(3,-5));
    printf("%d \n",multiplication(3,5));

    return 0;
}