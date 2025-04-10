#include<stdio.h>

void echange(int* a , int* b){
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}
int main(){
    int a = 10;
    int b = 20;
    printf("a= %d b=%d\n",a,b);
    echange(&a,&b);
    printf("a= %d b=%d",a,b);
    return 0;
}