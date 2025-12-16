# Auto-évaluation — TP4

## État des exercices

| Exercice | État | Remarques |
|---|---|---|
| 4.1 — Conversion infixe → postfixée | réalisé | `postfixe.c`, algorithme de Shunting-Yard |
| 4.2 — Parenthèses | réalisé | gestion des `(` et `)`, priorités et erreurs de parenthésage |
| 4.3 — Évaluation postfixée | réalisé | pile d'opérandes, ordre correct pour `-` et `/` |
| 4.4 — Intégration dans l'interpréteur | réalisé | `repl.c` utilise `evaluate_infix` |

## Bibliothèques utilisées

- `stdio.h` : messages d'erreur et formatage.
- `string.h` : `strlen`, `memcpy`, `strchr`.
- `ctype.h` : `isspace`, `isdigit`.
- `stdlib.h` et `errno.h` : `strtod` pour les opérandes réels.
- `math.h` : vérification des résultats finis dans le REPL.

## Références

- Sujet du TP4 (`TP4.md`).
- Algorithme de **Shunting-Yard** d'Edsger Dijkstra.
- Notation polonaise inverse (RPN) et évaluation par pile.
- Documentation C standard pour `strtod`.

## Difficulté

- Exercice 4.1 : moyen, il faut comprendre la priorité des opérateurs et la pile.
- Exercice 4.2 : moyen, gestion des parenthèses et des erreurs.
- Exercice 4.3 : moyen, ordre des opérandes pour la soustraction et la division.
- Exercice 4.4 : facile une fois les fonctions précédentes disponibles.

## Commentaires

- La conversion produit une chaîne de jetons séparés par des espaces.
- Le moins unaire est représenté par le jeton `u` pour ne pas le confondre avec la soustraction.
- Les erreurs de parenthèses, d'opérateur mal placé et de division par zéro sont explicites.
- Les nombres réels sont conservés (`1.2 * 4.0 = 4.8`), contrairement à une implémentation entière.
- Les tests couvrent la conversion, l'évaluation, les parenthèses et le moins unaire.
