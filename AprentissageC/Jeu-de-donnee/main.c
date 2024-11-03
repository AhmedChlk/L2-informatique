#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int age_min;
    int age_max;
} age_t;

typedef struct {
    int annee;
    age_t age;
    int nbr_admis;
    float pr_reussite;
} donnee_t;

typedef struct {
    int taille_max_jeu;
    donnee_t** tab_donnee;
    int nombre_element_present;
} jeu_donnee_t;

donnee_t* cree_donnee(int annee, age_t age, int nbr_admis, float pr_reussite) {
    donnee_t* d = (donnee_t*) malloc(sizeof(donnee_t));
    d->annee = annee;
    d->age = age;
    d->nbr_admis = nbr_admis;
    d->pr_reussite = pr_reussite;
    return d;
}

void reallouer(jeu_donnee_t* jeu_donnee) {
    int nouvelle_taille = jeu_donnee->taille_max_jeu * 2;
    donnee_t** nouveau_tableau = realloc(jeu_donnee->tab_donnee, nouvelle_taille * sizeof(donnee_t*));
    if (nouveau_tableau != NULL) {
        //printf("DEBUG: Réallocation réussie, nouvelle taille : %d\n", nouvelle_taille);
        jeu_donnee->tab_donnee = nouveau_tableau;
        jeu_donnee->taille_max_jeu = nouvelle_taille;
    } else {
        printf("ERREUR : Échec de la réallocation\n");
        exit(EXIT_FAILURE);
    }
}

void ajouter_donnee(donnee_t* d, jeu_donnee_t* jeu_donnee) {
    if (jeu_donnee->nombre_element_present == jeu_donnee->taille_max_jeu) {
        reallouer(jeu_donnee);
    }
    jeu_donnee->tab_donnee[jeu_donnee->nombre_element_present] = d;
    jeu_donnee->nombre_element_present++;
}

jeu_donnee_t* allouer(int taille_max_jeu) {
    jeu_donnee_t* J = (jeu_donnee_t*) malloc(sizeof(jeu_donnee_t));
    if (J != NULL) {
        J->taille_max_jeu = taille_max_jeu;
        J->nombre_element_present = 0;
        J->tab_donnee = (donnee_t**) malloc(taille_max_jeu * sizeof(donnee_t*));
        if (J->tab_donnee == NULL) {
            free(J);
            return NULL;
        }
    }
    return J;
}



void afficher_donnee(donnee_t d) {
    printf("-----------------------\n"
           "  annee : %d \n"
           "  [age_min ; age_max] : [%d,%d]\n"
           "  nombre admis : %d\n"
           "  pr reussite : %f \n"
           "----------------------\n",
           d.annee, d.age.age_min, d.age.age_max, d.nbr_admis, d.pr_reussite);
}

void afficher(jeu_donnee_t jeu_donnee) {
    for (int i = 0; i < jeu_donnee.nombre_element_present; i++) {
        afficher_donnee(*jeu_donnee.tab_donnee[i]);
    }
}

void liberer(jeu_donnee_t** jeu_donnee) {
    for (int i = 0; i < (*jeu_donnee)->nombre_element_present; i++) {
        free((*jeu_donnee)->tab_donnee[i]);
    }
    free((*jeu_donnee)->tab_donnee);
    free(*jeu_donnee);
    *jeu_donnee = NULL;
}

jeu_donnee_t* lire(const char* fname) {
    donnee_t* d = NULL;
    jeu_donnee_t* J = allouer(100);
    int annee, a_min, a_max, nb_bac;
    float p_bac;
    FILE *F = fopen(fname, "r");
    if(F != NULL) {
        while(fscanf(F, "%d %d %d %d %f", &annee, &a_min, &a_max, &nb_bac, &p_bac) != EOF) {
            d = cree_donnee(annee, (age_t){a_min, a_max}, nb_bac, p_bac);
            ajouter_donnee(d, J);
        }
        fclose(F);
    }
    return J;
}
jeu_donnee_t* copie(jeu_donnee_t* jeu_donnee) {
    jeu_donnee_t* J = allouer(jeu_donnee->taille_max_jeu);
    for (int i = 0; i < jeu_donnee->nombre_element_present; i++) {
        donnee_t* copie_donnee = cree_donnee(
            jeu_donnee->tab_donnee[i]->annee,
            jeu_donnee->tab_donnee[i]->age,
            jeu_donnee->tab_donnee[i]->nbr_admis,
            jeu_donnee->tab_donnee[i]->pr_reussite
        );
        ajouter_donnee(copie_donnee, J);
    }
    return J;
}

void permuter_donnee (donnee_t* d1 , donnee_t* d2){
    donnee_t temp;
    temp = *d1;
    *d1 = *d2;
    *d2 = temp;
}
void trie_bulle(jeu_donnee_t* jeu_donnee){
    for(int i=0;i<jeu_donnee->nombre_element_present -1;i++){
        for(int j=i+1;j<jeu_donnee->nombre_element_present-i-1;j++){
            if(jeu_donnee->tab_donnee[j+1]->annee < jeu_donnee->tab_donnee[j]->annee || ((jeu_donnee->tab_donnee[j+1]->annee == jeu_donnee->tab_donnee[j]->annee) && (jeu_donnee->tab_donnee[j+1]->pr_reussite > jeu_donnee->tab_donnee[j]->pr_reussite))){
                permuter_donnee (jeu_donnee->tab_donnee[j],jeu_donnee->tab_donnee[j+1]);
            }
        }
    }
}

jeu_donnee_t* extraire(jeu_donnee_t* jeu_donnee) {
    jeu_donnee_t* temp = copie(jeu_donnee);
    jeu_donnee_t* J = allouer(20);
    trie_bulle(temp);
    donnee_t* max_donnee = temp->tab_donnee[0];
    int annee_courante = max_donnee->annee;

    for (int i = 1; i < temp->nombre_element_present; i++) {
        donnee_t* current = temp->tab_donnee[i];
        if (current->annee != annee_courante) {
            donnee_t* copie_max_donnee = cree_donnee(
                max_donnee->annee,
                max_donnee->age,
                max_donnee->nbr_admis,
                max_donnee->pr_reussite
            );
            ajouter_donnee(copie_max_donnee, J);

            annee_courante = current->annee;
            max_donnee = current;
        } else if (current->nbr_admis > max_donnee->nbr_admis) {
            max_donnee = current;
        }
    }

    donnee_t* copie_max_donnee = cree_donnee(
        max_donnee->annee,
        max_donnee->age,
        max_donnee->nbr_admis,
        max_donnee->pr_reussite
    );
    ajouter_donnee(copie_max_donnee, J);

    liberer(&temp);
    return J;
}

int rechercher(int annee, jeu_donnee_t* jeu_donnee){
    for(int i=0;i<jeu_donnee->nombre_element_present;i++){
        if(jeu_donnee->tab_donnee[i]->annee == annee ){
            return i;
        }
    }
    return -1;
}
void supprimer(jeu_donnee_t* jeu_donnee,int indice){
    if(indice >= 0 && indice < jeu_donnee->nombre_element_present){
        free(jeu_donnee->tab_donnee[indice]);
        for(int i=indice;i<jeu_donnee->nombre_element_present -1;i++){
            jeu_donnee->tab_donnee[i] = jeu_donnee-> tab_donnee[i+1];
        }
        jeu_donnee->nombre_element_present--;
        jeu_donnee->tab_donnee[jeu_donnee->nombre_element_present] = NULL;
        

    }
}

int main() {
    jeu_donnee_t* T = lire("cc1_data.txt");
    jeu_donnee_t* J = extraire(T);
    afficher(*J);
    liberer(&T);

    return 0;
}
