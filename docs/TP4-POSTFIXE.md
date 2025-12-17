# TP4 — Expressions infixées, postfixées et piles

## Objectif

Le TP4 remplace l'évaluateur limité `A op B` du TP3 par une chaîne complète :

```text
expression infixe
      │
      ▼
 infix_to_postfix()        (Shunting-Yard, pile d'opérateurs)
      │
      ▼
 expression postfixée      « 3 4 5 * + »
      │
      ▼
 eval_postfix()            (pile d'opérandes)
      │
      ▼
 résultat (double)
```

## 1. Priorités et associativité

| Opérateur | Priorité | Associativité |
|---|---:|---|
| `+`, `-` binaires | 1 | gauche |
| `*`, `/` | 2 | gauche |
| `u` (moins unaire) | 3 | droite |

Le moins unaire est noté `u` dans la sortie postfixée. Cela évite de le confondre avec la
soustraction binaire et permet d'évaluer `-3 + 5` ou `2 * -3`.

## 2. Algorithme de Shunting-Yard

Pour chaque jeton, de gauche à droite :

1. **Nombre** : l'ajouter directement à la sortie.
2. **`(`** : l'empiler.
3. **`)`** : dépiler vers la sortie jusqu'à `(`, puis retirer `(`.
4. **Opérateur binaire** : dépiler tous les opérateurs de priorité supérieure ou égale, puis
   empiler l'opérateur courant.
5. **Moins unaire** : l'empiler directement (priorité 3, associativité droite).
6. À la fin, vider la pile dans la sortie.

Exemple :

```text
(3 + 4) * 5
3          → sortie : 3
(          → pile   : (
3          → sortie : 3
+          → pile   : ( +
4          → sortie : 3 4
)          → sortie : 3 4 +   pile : vide
*          → pile   : *
5          → sortie : 3 4 + 5
fin        → sortie : 3 4 + 5 *
```

## 3. Évaluation postfixée

On parcourt la chaîne postfixée :

- un nombre est empilé ;
- `u` remplace le sommet par son opposé ;
- un opérateur binaire dépile `droite` puis `gauche` et empile `gauche op droite`.

L'ordre est important pour `-` et `/` :

```text
3 2 -   → 3 - 2 = 1
3 2 /   → 3 / 2 = 1.5
```

À la fin, la pile doit contenir exactement une valeur.

## 4. Gestion des erreurs

La conversion et l'évaluation détectent :

- opérateur mal placé (`* 3`, `3 +`);
- opérandes consécutifs (`3 4`);
- parenthèse ouvrante non fermée ;
- parenthèse fermante sans ouvrante ;
- parenthèses vides `()`;
- pile saturée ;
- opérandes insuffisants pour un opérateur ;
- division par zéro ;
- expression trop longue pour le buffer de sortie.

## 5. Intégration au REPL

`repl.c` appelle `is_arithmetic_expression()` pour distinguer une expression d'une commande,
puis `evaluate_infix()` :

```text
> 3 + 4 * 5
23
> (3 + 4) * 5
35
> 1.2 * 4.0
4.8
> -3 + 5
2
```

## 6. Validation

```bash
make -C interpreteur
printf '3 + 4 * 5\n(3 + 4) * 5\n1.2 * 4.0\nquit\n' | ./interpreteur/interpreteur
make -C tests test
```

Les tests unitaires vérifient la conversion exacte, l'évaluation, les parenthèses, le moins
unaire et les erreurs.
