# AlgoDesImages

Ce projet regroupe mes travaux en algorithmique des images en L2 Informatique. Il inclut la manipulation des formats PGM et PPM, une compression/décompression simplifiée JPEG, ainsi que des transformations géométriques avec interpolation.

## Structure

- **src/**  
  Contient le code source réparti ainsi :  
  - `td1/pgm/` : Modules pour images PGM.  
  - `td1/ppm/` : Modules pour images PPM.  
  - `td1/jpeg/` : Compression/Décompression JPEG (PGM).  
  - `td2/transfomation_dimages/` : Transformations géométriques et interpolation.
- **include/**  
  Contient les fichiers d'en‑tête communs.
- **tests/**  
  Programmes de test pour chaque module.
- **data/**  
  Ressources image communes (e.g. `eye_s_asc.pgm`, `eye_s_asc.ppm`).

## Compilation

À la racine du projet, exécutez :
```bash
make
```

Pour lancer tous les tests :
```bash
make test
```

## Nettoyage

Pour supprimer les fichiers objets et exécutables :
```bash
make clean
```