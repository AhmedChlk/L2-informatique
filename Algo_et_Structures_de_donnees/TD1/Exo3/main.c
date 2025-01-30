#include <stdio.h>
#include <stdlib.h>

int fact_rec(int n){
    if(n < 0){
        //erreur
        return -1;
    }else if ( n == 0 || n == 1){
        return 1;
    }else{
        return n * fact_rec(n-1);
    }
}

int fact_non_rec(int n){
    if(n<0){
        return -1;
    }
    int fact = 1;
    for(int i=2;i<=n;i++){
            fact *= i;
    }
    return fact;
}

int fib_rec(int n){
    if(n == 0){
        return 0;
    }else if ( n == 1){
        return 1;
    }else {
        return fib_rec(n-1) + fib_rec(n-2);
    }
}

int fib_non_rec(int n){
    int* tab_fib =  (int*) malloc((n+1)*sizeof(int));
    tab_fib[0] = 0;
    tab_fib[1] = 1;
    for(int i=2;i<=n;i++){
        tab_fib[i] = tab_fib[i-1] + tab_fib[i-2];
    }
    return tab_fib[n];
}

int main(){
            printf("%d %d \n %d %d\n",fact_rec(5),fact_non_rec(5),fib_rec(12),fib_non_rec(12));               
    return 0;
}