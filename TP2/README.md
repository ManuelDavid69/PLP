# Auto-évaluation — TP2

## État des exercices

| Exercice | État | Remarques |
|---|---|---|
| 2.1 — Débogage avec GDB | réalisé | `erreurs.c` contient la version corrigée ; le bug d'origine est expliqué dans le fichier et dans `programmation_C.md` |
| 2.2 — Chaîne de compilation | réalisé | `aire.c`, compilation en étapes décrite dans la synthèse |
| 2.3 — Programme multi-fichiers | réalisé | `sphere.h`, `surface.c`, `volume.c`, `main.c` |
| 2.4 — Chaînes de caractères | réalisé | `chaine.c`, longueur, copie et concaténation |
| 2.5 — Données d'étudiant·e·s | réalisé | `bd_ecole.c`, cinq enregistrements et notes validées |
| 2.6 — Recherche dans un fichier | réalisé | `phrases.c` et fichier d'exemple `montexte.txt` |
| 2.7 — Couleurs et comptage | réalisé | `couleurs.c`, 100 couleurs et 7 couleurs distinctes |
| 2.8 — Recherche sans bibliothèque | réalisé | `chercher.c`, comparaison caractère par caractère |
| 2.9 — Synthèse | réalisé | `programmation_C.md` |

## Bibliothèques utilisées

- `stdio.h` : entrées/sorties, `printf`, `fgets`, `fopen`, `fclose`, `perror`.
- `string.h` : `strlen`, `strcpy`, `strcat`, `strstr`.
- `stdlib.h` : `strtof` pour les notes et les rayons.
- `math.h` : non nécessaire, la constante `PI` est définie localement pour rester portable.

## Références

- Sujet du TP2 (`TP2.md`) et cours de Principes des Langages de Programmation.
- Pages man de `gcc`, `gdb`, `fgets`, `strstr`, `strtof`.
- Norme ISO C11 pour les types `size_t` et les prototypes.

## Difficulté

- Exercices 2.1 à 2.4 : faciles à moyens.
- Exercice 2.5 : gestion des saisies multi-mots et validation des notes.
- Exercice 2.6 : lecture de fichier et comptage d'occurrences.
- Exercice 2.7 : recherche de doublons dans un tableau de structures.
- Exercice 2.8 : comparaison de chaînes sans utiliser `string.h`.

## Commentaires

- Tous les fichiers compilent avec `gcc -std=c11 -Wall -Wextra -Wpedantic -Werror`.
- Les chaînes sont lues avec `fgets` pour accepter les espaces.
- Les tailles de buffers sont vérifiées et les erreurs d'ouverture de fichier sont signalées.
- Le projet `sphere` illustre la compilation séparée et l'édition des liens.
- Les tests de sortie sont exécutés par `tests/test_tp2.sh`.
