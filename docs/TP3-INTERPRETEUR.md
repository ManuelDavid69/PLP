# TP3 — Architecture de l'interpréteur de commandes

## Objectif

Le TP3 transforme le squelette `repl.c` en un interpréteur de commandes extensible, puis
ajoute une première chaîne d'évaluation d'expressions arithmétiques simples.

```text
stdin ──► repl.c ──► COMMANDES[] ──► echo / help / version / date / quit
                    │
                    └──► lexer.c ──► parseur.c ──► evaluation.c
```

## 1. Boucle REPL

`main()` affiche le prompt `>`, lit une ligne avec `fgets`, retire le saut de ligne avec
`strcspn`, puis appelle `interpreter_ligne()`.

`interpreter_ligne()` :

1. copie la ligne et supprime les espaces de début et de fin ;
2. isole le premier mot (la commande) et le reste (les arguments) ;
3. parcourt le tableau `COMMANDES` ;
4. appelle la fonction associée si le nom correspond, sans tenir compte de la casse ;
5. sinon tente d'évaluer une expression simple ;
6. sinon affiche un message d'erreur explicite.

## 2. Table de commandes

```c
struct Commande {
    const char *nom;
    void (*fonction)(const char *arguments);
};
```

Cette table remplace la cascade de `if`/`else if` du squelette. Ajouter une commande revient
à ajouter une ligne dans `COMMANDES` et une fonction de traitement.

| Commande | Alias | Rôle |
|---|---|---|
| `echo <texte>` | — | affiche le texte |
| `help` | `aide` | affiche l'aide |
| `version` | — | affiche la version |
| `date` | — | affiche la date et l'heure |
| `quit` | `quitter` | arrête la boucle |

## 3. Lexer

Le lexer transforme la chaîne en jetons (`Token`) :

| Type | Exemple |
|---|---|
| `TOKEN_NUMBER` | `12`, `3.5`, `.5`, `1e-3` |
| `TOKEN_IDENTIFIER` | `x`, `π`, `nom_variable` |
| `TOKEN_STRING` | `"Bonjour"` |
| `TOKEN_PLUS`, `TOKEN_MINUS`, `TOKEN_STAR`, `TOKEN_SLASH` | `+ - * /` |
| `TOKEN_LPAREN`, `TOKEN_RPAREN` | `( )` |
| `TOKEN_DOT`, `TOKEN_EQUAL` | `. =` |
| `TOKEN_END`, `TOKEN_ERROR` | fin de chaîne, caractère invalide |

Les nombres sont convertis avec `strtod`. Le lexer refuse les formes ambiguës comme `1.2.3`
et les identifiants UTF-8 sont acceptés octet par octet.

## 4. Parseur et évaluateur

Le parseur du TP3 construit une structure `Expression` :

```c
typedef struct {
    double operande_gauche;
    double operande_droite;
    TokenType operation;
} Expression;
```

Il attend exactement : nombre, opérateur, nombre, fin de chaîne. L'évaluateur applique
l'opération et gère la division par zéro.

Cette version volontairement limitée sert de première étape. Le TP4 la remplace dans le REPL
par un convertisseur infixe → postfixe qui gère les priorités et les parenthèses.

## 5. Validation

```bash
make -C interpreteur
printf '2 + 3\n1.2 * 4.0\nquit\n' | ./interpreteur/interpreteur
make -C tests test
```

Résultat attendu :

```text
> 5
> 4.8
```

Les tests unitaires couvrent les jetons, les erreurs de syntaxe, les quatre opérations et la
division par zéro.
