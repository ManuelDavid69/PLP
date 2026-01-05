# TP2 — Chaîne de compilation, chaînes et structures

## Objectif

Le TP2 relie quatre thèmes : le débogage avec GDB, la chaîne de compilation GCC, la
manipulation des chaînes et la gestion de données avec des structures et des fichiers.

La synthèse détaillée demandée à l'exercice 2.9 se trouve dans
[`TP2/src/programmation_C.md`](../TP2/src/programmation_C.md). Ce document présente les choix
d'implémentation du dépôt.

## 1. Débogage

`erreurs.c` contient la version corrigée du programme fautif. Le commentaire d'en-tête rappelle
le bug d'origine :

```c
for (int compteur = 0; compteur < sizeof(tableau); compteur++)
```

`sizeof(tableau)` vaut 400 octets, pas 100 éléments. La correction utilise `size_t` et
`sizeof(tableau) / sizeof(tableau[0])`.

## 2. Compilation séparée

Le projet `sphere` est découpé en :

- `sphere.h` : prototypes ;
- `surface.c` : `calculer_surface` ;
- `volume.c` : `calculer_volume` ;
- `main.c` : point d'entrée.

Le `Makefile` de `TP2/` compile chaque fichier séparément, puis relie `main.o`, `surface.o` et
`volume.o`. Modifier `volume.c` ne force pas la recompilation de `main.c`.

## 3. Chaînes de caractères

`chaine.c` lit deux lignes complètes avec `fgets`, retire le saut de ligne, puis affiche :

- les longueurs avec `strlen` ;
- une copie avec `strcpy` ;
- la concaténation avec `strcat`.

Les buffers sont dimensionnés pour contenir le terminateur `'\0'`.

## 4. Structures et fichiers

`bd_ecole.c` stocke cinq étudiant·e·s dans un tableau de structures. Les champs texte sont lus
avec `fgets` puis copiés avec `strcpy` dans des buffers de taille adaptée. Les notes sont
converties avec `strtof` et validées entre 0 et 20.

`phrases.c` lit un fichier ligne par ligne, compte les occurrences non chevauchantes avec
`strstr`, puis affiche le numéro de ligne et le total. Le fichier `montexte.txt` sert
d'exemple.

`couleurs.c` stocke 100 couleurs RGBA, puis compare chaque couleur aux couleurs distinctes déjà
trouvées. Le jeu de couleurs est déterministe pour que les tests soient reproductibles.

`chercher.c` effectue la recherche sans `strcmp` ni `strstr` : deux boucles comparent les
caractères jusqu'au terminateur.

## 5. Validation

```bash
make -C TP2
bash tests/test_tp2.sh
```

Les tests couvrent l'aire, la sphère, les chaînes, les étudiant·e·s, la recherche dans un
fichier, les couleurs et la recherche sans bibliothèque.
