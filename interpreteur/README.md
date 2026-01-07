# Interpréteur (TP3, TP4 et TP5)

Les TP3, TP4 et TP5 construisent **un seul et même interpréteur**, de manière itérative. Tout son
code source se trouve dans ce dossier, dans `src/` : chaque TP complète les fichiers du TP
précédent au lieu d'en recopier une nouvelle version.

| TP | Étape | Fichiers concernés |
|---|---|---|
| TP3 | Commandes (`echo`, `help`, `version`, `date`, `quit` et leurs équivalents français), puis lexer, parseur et évaluateur d'expressions simples `A op B` | `repl.c`, `lexer.c/.h`, `parseur.c/.h`, `evaluation.c/.h` |
| TP4 | Notation infixée → postfixée, parenthèses, moins unaire, évaluation par pile | `postfixe.c/.h` (+ `repl.c`) |
| TP5 | Variables typées (table de symboles, noms UTF-8) et expressions lambda | `symboles.c/.h`, `lambda.c/.h` (+ `repl.c`) |

## Modules

```text
repl.c        boucle REPL, commandes, aiguillage des expressions
lexer.c/.h    analyse lexicale : nombres, identifiants UTF-8, chaînes, opérateurs
parseur.c/.h  parseur simple « A op B » du TP3
evaluation.c/.h évaluateur simple du TP3
postfixe.c/.h Shunting-Yard, évaluation postfixée, détection d'expression
symboles.c/.h table de symboles typée et gestion des affectations
lambda.c/.h   parsing, substitution et évaluation des expressions lambda
```

Le parseur et l'évaluateur du TP3 restent compilés et testés ; le REPL utilise l'évaluateur
complet du TP4 (`evaluate_infix`).

## Compilation et exécution

Le `Makefile` compile chaque fichier `.c` séparément en un fichier objet `.o`, puis lie les
objets en un exécutable. Seuls les fichiers modifiés sont recompilés.

```bash
cd interpreteur
make            # gcc -std=c11 -Wall -Wextra -Wpedantic -O2
./interpreteur
```

Exemple de session :

```text
> echo Bonjour
Echo: Bonjour

> 3 + 4 * 5
23

> (3 + 4) * 5
35

> x = 4
Variable x définie avec la valeur 4 (entier)

> (lambda x.x + 2 * x) 3
9

> quit
Arrêt...
```

Autres cibles :

- `make run` : compile et lance l'interpréteur ;
- `make debug` : recompile avec `-ggdb3 -O0` pour GDB ;
- `make clean` : supprime les `.o` et l'exécutable.

Sans `make` :

```bash
gcc -std=c11 -Wall -Wextra -Wpedantic -o interpreteur src/*.c -lm
```

## Tests

Depuis la racine du dépôt :

```bash
make -C tests test          # tests unitaires C
bash tests/test_interpreteur.sh  # test de bout en bout du REPL
```

Les tests couvrent le lexer, le parseur, l'évaluateur, la conversion postfixée, les parenthèses,
le moins unaire, la table de symboles et les lambdas.

## Documentation

- [Architecture du TP3](../docs/TP3-INTERPRETEUR.md)
- [Expressions postfixées du TP4](../docs/TP4-POSTFIXE.md)
- [Variables et lambda du TP5](../docs/TP5-VARIABLES-LAMBDA.md)
