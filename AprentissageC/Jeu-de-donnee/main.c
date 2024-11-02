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

// Création d'une nouvelle donnée
donnee_t* cree_donnee(int annee, age_t age, int nbr_admis, float pr_reussite) {
    donnee_t* d = (donnee_t*) malloc(sizeof(donnee_t));
    d->annee = annee;
    d->age = age;
    d->nbr_admis = nbr_admis;
    d->pr_reussite = pr_reussite;
    return d;
}

void reallouer(jeu_donnee_t* jeu_donnee) {
    int nouvelle_taille = jeu_donnee->taille_max_jeu + 1;
    donnee_t** nouveau_tableau = realloc(jeu_donnee->tab_donnee, nouvelle_taille * sizeof(donnee_t*));
    if (nouveau_tableau != NULL) {
        printf("DEBUG: Réallocation réussie, nouvelle taille : %d\n", nouvelle_taille);
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

// Libère le jeu de données
void liberer(jeu_donnee_t** jeu_donnee) {
    for (int i = 0; i < (*jeu_donnee)->nombre_element_present; i++) {
        free((*jeu_donnee)->tab_donnee[i]);
    }
    free((*jeu_donnee)->tab_donnee);
    free(*jeu_donnee);
    *jeu_donnee = NULL;
}

// Lecture des données à partir d'un fichier
jeu_donnee_t* lire(const char* fname) {
    donnee_t* d = NULL;
    jeu_donnee_t* J = allouer(10);  // Taille initiale à 10 pour éviter des realloc trop fréquents
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

int main() {
    jeu_donnee_t* T = lire("cc1_data.txt");
    if (T != NULL) {
        //afficher(*T);
        liberer(&T);
    }
    return 0;
}
