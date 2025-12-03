# Auto-évaluation — TP3

## État des exercices

| Exercice | État | Remarques |
|---|---|---|
| 3.1 — Prise en main de l'interpréteur | réalisé | `repl.c`, commandes `echo`, `quit`, `date` |
| 3.2 — `help`, `version` et table de commandes | réalisé | fonctions dédiées et tableau `COMMANDES` |
| 3.3 — Commandes en français | réalisé | `aide`, `quitter`, comparaison insensible à la casse |
| 3.4 — Lexer, parseur et évaluateur | réalisé | `lexer.c/.h`, `parseur.c/.h`, `evaluation.c/.h` |

## Bibliothèques utilisées

- `stdio.h` : lecture des commandes, `printf`, `fgets`, `fflush`.
- `string.h` : `strlen`, `strcpy`, `strchr`, `strcspn`, `strcmp`.
- `ctype.h` : `isspace`, `isdigit`, `isalpha`, `tolower`.
- `time.h` : commande `date`.
- `stdlib.h` et `errno.h` : conversion des nombres dans le lexer.

## Références

- Sujet du TP3 (`TP3.md`).
- `interpreteur/README.md` pour la compilation et l'utilisation du `Makefile`.
- Algorithme de Shunting-Yard (Dijkstra), utilisé à partir du TP4.
- Documentation C standard pour `strtod` et les types `size_t`.

## Difficulté

- Exercices 3.1 à 3.3 : faciles, surtout de la manipulation de chaînes et de tableaux de fonctions.
- Exercice 3.4 : moyen, découpage lexer → parseur → évaluateur et gestion des erreurs.

## Commentaires

- Les commandes sont insensibles à la casse (`HELP`, `Aide`, `QUITTER` fonctionnent).
- `echo` conserve les espaces et les accents du texte saisi.
- Le lexer distingue nombres, identifiants UTF-8, chaînes, opérateurs et parenthèses.
- Le parseur du TP3 se limite volontairement à `A op B` ; le TP4 ajoute les expressions
  complètes avec priorités et parenthèses.
- Les tests unitaires du dossier `tests/` couvrent le lexer, le parseur et l'évaluateur.
