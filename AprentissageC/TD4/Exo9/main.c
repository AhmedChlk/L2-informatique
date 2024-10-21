#include <stdio.h>

int main(){
    int i;
    int* p;
    i = 10;
    p = &i;
    printf("la valeur de i : %d la valeur de p : %d\n",i,*p);
    *p = 20;
    printf("la valeur de i : %d la valeur de p : %d\n",i,*p);
    printf("l\'adresse de i : %p\n",&i);
    printf("la  valeur de p : %p \n",p);
    return 0;
}