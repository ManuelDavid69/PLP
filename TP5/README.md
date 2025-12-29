# Auto-évaluation — TP5

## État des exercices

| Exercice | État | Remarques |
|---|---|---|
| 5.1 — Gestion des variables | réalisé | `symboles.c/.h`, table typée, affectation et lecture |
| 5.2 — Expressions lambda | réalisé | `lambda.c/.h`, parsing, substitution et évaluation |

## Bibliothèques utilisées

- `stdio.h` : affichage des valeurs, des définitions et des erreurs.
- `string.h` : comparaisons, copies et manipulation des noms.
- `ctype.h` : validation des noms et suppression des espaces.
- `stdlib.h` et `errno.h` : `strtoll` et `strtod` pour les valeurs.
- `math.h` : `isfinite` pour refuser les arguments non finis.

## Références

- Sujet du TP5 (`TP5.md`).
- Calcul lambda : syntaxe `(lambda x.expression) argument`.
- Documentation C standard pour `strtoll`, `strtod` et les encodages UTF-8.

## Difficulté

- Exercice 5.1 : moyen, il faut séparer le nom, la valeur et le type, puis refuser les
  changements de type.
- Exercice 5.2 : élevé, il faut parser une expression imbriquée, substituer le paramètre et
  réutiliser l'évaluateur du TP4.

## Commentaires

- Les noms de variables peuvent contenir des caractères UTF-8 (`π`, `résultat`, etc.).
- Trois types sont supportés : entier, nombre réel et chaîne de caractères.
- Une variable ne peut pas changer de type : `x = 4` puis `x = 12.3` produit une erreur.
- La substitution lambda se fait sur les jetons du lexer, pas par simple remplacement de
  sous-chaîne : `x` ne remplace pas le `x` de `exp`.
- Les variables déjà définies peuvent être utilisées comme argument ou dans le corps de la
  lambda.
- Les tests couvrent les types, les erreurs, les lambdas imbriquées et les arguments réels.
