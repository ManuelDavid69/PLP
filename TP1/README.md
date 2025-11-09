# Auto-évaluation — TP1

## État des exercices

| Exercice | État | Remarques |
|---|---|---|
| 1.1 — Bonjour le Monde | réalisé | `bonjour.c` |
| 1.2 — Aire et périmètre d'un cercle | réalisé | `cercle.c`, rayon validé et `PI` défini de façon portable |
| 1.3 — Tailles des types de base | réalisé | `sizeof_types.c`, affichage avec `%zu` |
| 1.4 — Variables et types de base | réalisé | `variables.c`, valeurs signées, non signées et flottantes |
| 1.5 — Opérateurs | réalisé | `operateurs.c`, arithmétique, comparaisons et logique |
| 1.6 — Triangle rectangle | réalisé | `boucles.c`, versions `for` et `while`, taille bornée à 1..9 |
| 1.7 — Structures de contrôle | réalisé | `controle.c`, boucle `for`, compteurs `while` et `do..while` |
| 1.8 — Calculs et opérations bit à bit | réalisé | `calculs.c`, `switch`, division/modulo par zéro gérés |
| 1.9 — Affichage binaire | réalisé | `binaire.c`, divisions par 2, bits groupés par 4 |

## Bibliothèques utilisées

- `stdio.h` : `printf`, `scanf`, `putchar`, `fprintf`.
- `limits.h` : `UCHAR_MAX`, `USHRT_MAX`, `UINT_MAX`, `ULONG_MAX`, `ULLONG_MAX`.
- `stdlib.h` et `errno.h` : conversion des arguments de `binaire.c` avec `strtoul`.
- Aucune dépendance à `M_PI` : la constante `PI` est définie localement pour rester portable.

## Références

- Sujet du TP1 (`TP1.md`) et cours de Principes des Langages de Programmation.
- Pages man de `gcc`, `printf`, `scanf`, `strtoul`.
- Norme ISO C11 pour les formats `%zu`, `%lld`, `%llu` et `%Lf`.

## Difficulté

- Exercices 1.1 à 1.5 : faciles, révision des types et des opérateurs.
- Exercice 1.6 : logique des bords et de l'intérieur du triangle.
- Exercice 1.7 : combinaison de conditions qui se chevauchent ; le `else if` évite les doublons.
- Exercices 1.8 et 1.9 : opérateurs bit à bit, gestion des erreurs et ordre des bits.

## Commentaires

- Tous les programmes compilent avec `gcc -std=c11 -Wall -Wextra -Wpedantic -Werror`.
- Les entrées sont vérifiées (`scanf`, `strtoul`) et les erreurs sont écrites sur `stderr`.
- `binaire.c` accepte aussi des valeurs en arguments, ce qui rend les tests reproductibles.
- Les traces de test sont exécutées par `tests/test_tp1.sh`.
