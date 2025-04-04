# Notes sur les Bonnes Pratiques en Programmation C

Ces notes résument les concepts et pratiques professionnelles que j'ai appris durant cette Exercice de TD

---

## 1. Séparation des Responsabilités

- **Principe :**
  - Diviser le code en modules fonctionnels distincts.
  - Séparer la logique métier (traitement, transformation d'images) de la gestion des entrées/sorties (lecture/écriture de fichiers) et de l'interaction utilisateur.

- **Avantages :**
  - Amélioration de la lisibilité.
  - Facilité de maintenance et de réutilisation.
  - Simplification des tests unitaires et du débogage.

- **Exemples Concrets :**
  - Créer une fonction auxiliaire `write_comment` pour gérer l'écriture d'un commentaire dans un fichier.
  - Séparer les fonctions de lecture/écriture ASCII (`P3`) et binaire (`P6`) dans des modules distincts.

---

## 2. Gestion Fine des Erreurs

- **Principe :**
  - Ne pas interrompre l'exécution du programme avec des appels directs à `exit()`.
  - Propager les erreurs via des codes de retour ou des valeurs `NULL` pour permettre une gestion fine par l'appelant.

- **Bonnes Pratiques :**
  - Vérifier systématiquement les retours des fonctions critiques comme `malloc`, `fopen`, et `fscanf`.
  - Exemple :
    ```c
    ppm_t* img = ppm_alloc(height, width, max_value);
    if (img == NULL) {
        // Gestion de l'erreur (affichage de message, libération des ressources, etc.)
    }
    ```

---

## 3. Utilisation de `const` et Types Cohérents

- **Principe :**
  - Utiliser le modificateur `const` pour les paramètres et variables qui ne doivent pas être modifiés.
  - Employer des types cohérents (`unsigned int`, `size_t`) pour les dimensions et indices.

- **Exemple :**
  ```c
  void ppm_print(const ppm_t* img) {
      // La fonction ne modifie pas l'image
  }



## 5 Chaînes Littérales et Déclaration de Chaînes
- **Chaîne Littérale :**
    Une chaîne déclarée comme :
```c
const char* comment = "Generated by Choulak Ahmed";
```
    est stockée en mémoire en lecture seule.
- **Conseils :**
    - Toujours déclarer une chaîne littérale comme const char* pour éviter toute modification accidentelle.
- **Attention :**
    - Bien que char* comment = "..." fonctionne, modifier cette chaîne entraînera un comportement indéfini.