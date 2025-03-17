#include <stdio.h>
#include<string.h>
#define M 26
void analyse_frequentiel(const char *message, int taille){
    int i;
    int freq[26] = {0};
    for(i = 0; i < taille; i++){
        if(message[i] >= 'a' && message[i] <= 'z'){
            freq[message[i] - 'a']++;
        }
    }
    for(i = 0; i < 26; i++){
        printf("%c : %d\n", 'a' + i, freq[i]);
    }
}

int calcul_inversible(int a){
    int i;
    for(i=1;i<M;i++){
        if((a*i)%M == 1){
            return i;
        }   
    }
    return -1;
}

int normalisation(int n){
    return (n + M*M) % M;
}

void resolution_systeme(char lettre_claire1, char lettre_chiffree1, char lettre_claire2, char lettre_chiffree2,int *a, int *b){
    if(calcul_inversible(((lettre_claire1 - lettre_claire2)+ M) % M) == -1){
        printf("Le systeme n'a pas de solution\n");
        return;
    }else{
        *a = ((((lettre_chiffree1 - lettre_chiffree2)+M)%M) * calcul_inversible(((lettre_claire1 - lettre_claire2)+M)%M))% M;
        *b = ((lettre_chiffree1 - normalisation(*a * lettre_claire1)) + M) % M;
        printf("a = %d , b = %d\n",*a,*b);
    }

}



void dechifrement_affine(const char *message, int taille, int a, int b){
    for(int i=0;i<taille;i++){
        printf("%c",(normalisation(calcul_inversible(a)*(normalisation(message[i]-'a' - b) )) % M) + 'a' );
    }
}
int main(){
    const char* message = "ntjmpumgxpqtstgqpgtxpnchumtputgfsftgthnngxnchumwxootrtumhpyctgktjqtjchfooxujqhgztumxpotjxotfoqtohrxumhzutwftgtopfmntjmpuatmfmshodpfrxpjjtqtghbxuj";
    dechifrement_affine(message,strlen(message),3,7);
    return 0;
}