# Algorithmes et Structures de Données

Implémentation d'une bibliothèque de manipulation d'arbres binaires de recherche en C, incluant diverses fonctions de parcours, insertion, recherche et analyse. Ce projet démontre mes compétences en algorithmique, structures de données et programmation C.

## Fonctionnalités implémentées

- Création et destruction d'arbres binaires
- Insertion et recherche de valeurs
- Parcours (préfixe, infixe, postfixe)
- Implémentation itérative et récursive
- Calcul de hauteur et équilibrage
- Tests unitaires complets

## Organisation du code

- **src/**  
  - `arbre_utils.c` : Implémentation des opérations sur les arbres binaires
  - `main.c` : Programme de démonstration  

- **include/**  
  - `arbre_utils.h` : Interface de la bibliothèque d'arbres binaires

- **tests/**  
  - `test_arbre.c` : Tests unitaires validant le comportement des fonctions

- **Makefile**  
  - Automatisation de la compilation et des tests

## Compilation et exécution

```bash
# Compiler le programme principal
make

# Exécuter les tests unitaires
make run_tests

# Nettoyer le projet
make clean
```

## Compétences démontrées

- Programmation en C
- Manipulation de structures de données complexes
- Algorithmes de parcours d'arbres
- Tests unitaires
- Organisation de code modulaire
- Utilisation de Makefile

## Documentation

Chaque fonction est documentée en détail dans les fichiers d'en-tête, et le programme de test sert d'exemple d'utilisation de la bibliothèque.