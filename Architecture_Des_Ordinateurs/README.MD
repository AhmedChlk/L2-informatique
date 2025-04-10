# Architecture Des Ordinateurs

Ce dépôt contient mes travaux pratiques et projet final du cours d'Architecture des Ordinateurs. Il comprend plusieurs circuits numériques conçus avec Digital Logic Simulator (.dig) illustrant les concepts fondamentaux de l'architecture d'un ordinateur, du circuit simple aux implémentations complètes de processeur.

## Structure du projet

### Pipeline RV32I
Implémentation complète d'un processeur RISC-V (RV32I) avec architecture pipeline, comprenant:
- Étages du pipeline (IF, ID, EX, MEM, WB)
- Banc de registres
- Unité Arithmétique et Logique (UAL)
- Gestion des branchements
- Circuits de contrôle

### TD1 - Circuits combinatoires
- **Exo2**: Décodeurs (2→4, 3→8) et multiplexeurs (MUX 2:1, MUX 8:1)
- **Exo3**: Additionneur (1 bit, 8 bits) avec propagation de carry
- **Exo5**: Conception d'UAL avec opérations arithmétiques et logiques (AND, OR, XOR)

### TD2 - Circuits séquentiels
- **Exo1**: Registres 8 bits et registres à décalage
- **Exo2**: Compteurs (simple, avec reset, décompteur, à saturation)
- **Exo3**: Multiplieur séquentiel avec circuit de contrôle

### TD3 - Chemin de données
Implémentation progressive d'un chemin de données (datapath):
- Banc de registres
- UAL
- Gestion des branchements
- Différentes versions du chemin de données (1.1 à 1.4)

## Technologies et compétences

- Conception de circuits numériques
- Architecture de processeur RISC-V
- Circuits combinatoires et séquentiels
- Pipeline d'exécution d'instructions
- Utilisation de Digital Logic Simulator

## Utilisation

Ces fichiers .dig peuvent être ouverts et simulés avec le logiciel [Digital](https://github.com/hneemann/Digital), un simulateur de circuits logiques open-source.

Pour chaque exercice:
1. Ouvrez le fichier .dig correspondant dans Digital
2. Utilisez le mode simulation pour observer le comportement du circuit
3. Modifiez les entrées pour tester différents scénarios

## Points forts du projet

- Implémentation complète d'un processeur RISC-V pipeliné
- Progression pédagogique des circuits simples aux architectures complexes
- Application pratique des concepts théoriques d'architecture des ordinateurs