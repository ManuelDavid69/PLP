# PLP — Travaux pratiques de Principes des Langages de Programmation (C)

![C CI](https://github.com/ManuelDavid69/PLP/actions/workflows/ci.yml/badge.svg)
![C11](https://img.shields.io/badge/C-C11-blue)
![GCC](https://img.shields.io/badge/GCC-11%2B-orange)
![License](https://img.shields.io/badge/License-GPLv3-green)

Projet du cours de **Principes des Langages de Programmation** (CPE Lyon) : les cinq travaux
pratiques du semestre, en langage **C**, avec un interpréteur construit progressivement des
TP3 au TP5.

> Squelette, énoncés et interfaces fournis par **John Samuel** dans le dépôt
> [`johnsamuelwrites/PLP`](https://github.com/johnsamuelwrites/PLP).
> Les exercices, l'interpréteur, les tests et la documentation de ce dépôt ont été réalisés par
> [ManuelDavid69](https://github.com/ManuelDavid69).

---

## Sommaire

- [Aperçu](#aperçu)
- [Les cinq TP](#les-cinq-tp)
- [L'interpréteur en action](#linterpréteur-en-action)
- [Architecture de l'interpréteur](#architecture-de-linterpréteur)
- [Choix techniques](#choix-techniques)
- [Compiler et exécuter](#compiler-et-exécuter)
- [Tests](#tests)
- [Structure du dépôt](#structure-du-dépôt)
- [Documentation](#documentation)
- [Crédits et licence](#crédits-et-licence)

---

## Aperçu

- **TP1** : neuf programmes autonomes sur les types, opérateurs, boucles et opérations bit à bit.
- **TP2** : débogage GDB, chaîne de compilation, chaînes de caractères, structures, fichiers,
  recherche de phrases et comptage de couleurs.
- **TP3** : interpréteur de commandes avec `echo`, `help`/`aide`, `version`, `date`,
  `quit`/`quitter`, puis lexer, parseur et évaluateur d'expressions `A op B`.
- **TP4** : conversion infixe → postfixée (Shunting-Yard), parenthèses, moins unaire et
  évaluation par pile.
- **TP5** : table de symboles typée (entier, réel, chaîne, noms UTF-8), affectations,
  lecture de variables et expressions lambda.
- **Plus de 260 assertions unitaires** et des tests de sortie pour les programmes autonomes.
- **CI GitHub Actions** : compilation et tests sur Ubuntu, avec un build strict `-Werror`.

---

## Les cinq TP

| TP | Contenu | Fichiers principaux | Documentation |
|---|---|---|---|
| **TP1 — Bases du C** | Types, `sizeof`, opérateurs, boucles, `switch`, binaire | `TP1/src/*.c` | [docs/TP1-BASES.md](docs/TP1-BASES.md) |
| **TP2 — Chaîne de compilation** | GDB, GCC, chaînes, structures, fichiers | `TP2/src/*.c` | [docs/TP2-CHAINE-COMPILATION.md](docs/TP2-CHAINE-COMPILATION.md) |
| **TP3 — Interpréteur** | Commandes, lexer, parseur, évaluateur simple | `interpreteur/src/` | [docs/TP3-INTERPRETEUR.md](docs/TP3-INTERPRETEUR.md) |
| **TP4 — Postfixé** | Shunting-Yard, parenthèses, pile d'opérandes | `interpreteur/src/postfixe.c` | [docs/TP4-POSTFIXE.md](docs/TP4-POSTFIXE.md) |
| **TP5 — Variables et lambda** | Table de symboles, types, lambdas | `interpreteur/src/symboles.c`, `lambda.c` | [docs/TP5-VARIABLES-LAMBDA.md](docs/TP5-VARIABLES-LAMBDA.md) |

Chaque dossier `TPn/` contient aussi :

- `TPn.md` : le sujet original ;
- `README.md` : l'auto-évaluation, les bibliothèques, les références et les difficultés ;
- `CONTRIBUTORS.md` : la liste des auteurs.

---

## L'interpréteur en action

```text
$ make -C interpreteur
$ ./interpreteur/interpreteur
Interpréteur PLP 1.0 — tapez 'help' ou 'aide'.
> echo Bonjour à tous
Echo: Bonjour à tous

> help
Commandes disponibles :
  echo <texte>      affiche le texte fourni
  date              affiche la date et l'heure courantes
  version           affiche la version de l'interpréteur
  help / aide       affiche cette aide
  quit / quitter    quitte l'interpréteur
  x = valeur        affecte une valeur à une variable typée
  x                 affiche la valeur d'une variable
  <expression>      évalue une expression, par exemple (3 + 4) * 5
  (lambda x.expr) v applique une fonction anonyme à une valeur

> 3 + 4 * 5
23

> (3 + 4) * 5
35

> 1.2 * 4.0
4.8

> x = 4
Variable x définie avec la valeur 4 (entier)

> x
4

> x = 12.3
Erreur : changement de type non autorisé pour la variable x

> π = 3.14
Variable π définie avec la valeur 3.14 (nombre réel)

> (lambda x.x + 2 * x) 3
9

> (lambda x.(x + 2) * x) 4
24

> y
Erreur : la variable y n'est pas définie

> quitter
Arrêt...
```

---

## Architecture de l'interpréteur

```text
repl.c
  │
  ├── COMMANDES[] ──► echo, help/aide, version, date, quit/quitter
  │
  ├── lambda.c ─────► parsing de (lambda x.expr) argument
  │       │
  │       ├── symboles.c ──► résolution des variables libres
  │       └── postfixe.c ──► évaluation après substitution
  │
  ├── symboles.c ───► affectations, lecture, types
  │
  └── postfixe.c
          ├── lexer.c ─────► nombres, identifiants UTF-8, opérateurs
          ├── Shunting-Yard ─► infixe → postfixé
          └── pile d'opérandes ─► résultat (double)
```

Le **lexer** est commun au TP3, au TP4 et au TP5. Le parseur simple du TP3 (`parseur.c` +
`evaluation.c`) reste disponible et testé ; le REPL utilise l'évaluateur complet du TP4.

---

## Choix techniques

### 1. C11, sans dépendance externe

Tout le projet compile avec `gcc -std=c11` et la bibliothèque mathématique (`-lm`). Il n'y a
aucune bibliothèque tierce : les tests unitaires utilisent un petit framework maison dans
`tests/test_framework.h`.

### 2. Une constante π portable

`M_PI` n'est pas garanti par la norme C. Les programmes définissent localement :

```c
#define PI 3.14159265358979323846
```

### 3. Séparation lexer → parseur → évaluateur

Le TP3 introduit les trois couches. Le TP4 remplace l'évaluateur limité `A op B` par une
conversion infixe → postfixée, sans casser les modules du TP3, toujours couverts par les tests.

### 4. Shunting-Yard et moins unaire

La conversion utilise une pile d'opérateurs et les priorités :

| Opérateur | Priorité |
|---|---:|
| `+`, `-` binaires | 1 |
| `*`, `/` | 2 |
| `u` (moins unaire) | 3 |

Le moins unaire est émis sous forme du jeton `u` dans la sortie postfixée. Cela permet
d'évaluer `-3 + 5`, `2 * -3` ou `3 - -2` sans confondre le signe et la soustraction.

### 5. Table de symboles typée

Trois types sont supportés :

- `VAR_INT` : `long long`, par exemple `x = 12` ;
- `VAR_REAL` : `double`, par exemple `π = 3.14` ;
- `VAR_STRING` : `char[256]`, par exemple `z = "Bonjour"`.

Une variable ne peut pas changer de type. Les noms sont comparés octet par octet, ce qui
accepte les noms UTF-8 comme `π` ou `résultat`.

### 6. Substitution lambda par jetons

La substitution du paramètre ne se fait pas avec un `strstr` naïf. Le corps de la lambda est
découpé par le lexer, puis seuls les identifiants **exactement égaux** au paramètre sont
remplacés. `x` ne remplace donc pas le `x` de `exp`.

### 7. Entrées robustes et erreurs explicites

- Les chaînes sont lues avec `fgets` pour accepter les espaces.
- Les conversions utilisent `strtoll` et `strtod` avec vérification de `errno`.
- Les divisions par zéro, parenthèses manquantes, types incompatibles et variables inconnues
  produisent des messages explicites.
- Les buffers sont bornés et les tailles vérifiées.

### 8. Tests et intégration continue

Les tests unitaires couvrent le lexer, le parseur, l'évaluateur, la conversion postfixée, la
table de symboles et les lambdas. Les scripts de sortie vérifient les programmes TP1/TP2 et le
REPL de bout en bout. La CI rejoue tout et ajoute un build strict `-Werror`.

---

## Compiler et exécuter

Prérequis : **GCC** (ou un compilateur C11 compatible) et **GNU Make**.

```bash
# Tout compiler
make all

# Compiler un TP en particulier
make -C TP1
make -C TP2
make -C interpreteur

# Lancer l'interpréteur
make -C interpreteur run
# ou
./interpreteur/interpreteur
```

Exemples de programmes autonomes :

```bash
./TP1/bin/bonjour
./TP1/bin/binaire 0 4096 65536 65535 1024
printf '5\n' | ./TP1/bin/boucles
./TP2/bin/sphere
printf 'TP2/src/montexte.txt\nBonjour\n' | ./TP2/bin/phrases
```

Sous Windows, les binaires sont dans `TP1/bin/`, `TP2/bin/` et `interpreteur/`. Le projet a été
développé et testé avec GCC sous Linux (WSL) ; il n'utilise aucune API spécifique à un système.

---

## Tests

```bash
# Tests unitaires + tests de sortie TP1/TP2 + tests du REPL
make test

# Uniquement les tests unitaires C
make -C tests test

# Uniquement un programme ou un TP
bash tests/test_tp1.sh
bash tests/test_tp2.sh
bash tests/test_interpreteur.sh
```

| Suite | Couverture |
|---|---|
| `tests/test_lexer.c` | nombres, identifiants UTF-8, chaînes, opérateurs, erreurs |
| `tests/test_parseur.c` | expression `A op B`, erreurs de syntaxe |
| `tests/test_evaluation.c` | quatre opérations, division par zéro |
| `tests/test_postfixe.c` | conversion, parenthèses, moins unaire, évaluation |
| `tests/test_symboles.c` | types, changement de type, table pleine, noms |
| `tests/test_lambda.c` | parsing, substitution, argument variable, erreurs |
| `tests/test_tp1.sh` | sorties des neuf programmes du TP1 |
| `tests/test_tp2.sh` | sorties des programmes du TP2 |
| `tests/test_interpreteur.sh` | commandes, expressions, variables et lambdas |

---

## Structure du dépôt

```text
PLP/
├── TP1/
│   ├── src/                 9 programmes C autonomes
│   ├── Makefile
│   ├── README.md            auto-évaluation
│   ├── CONTRIBUTORS.md
│   └── TP1.md               sujet
├── TP2/
│   ├── src/                 programmes, sphere.h, montexte.txt, synthèse
│   ├── Makefile
│   ├── README.md
│   ├── CONTRIBUTORS.md
│   └── TP2.md
├── TP3/                     sujet, auto-évaluation, contributeurs
├── TP4/                     sujet, auto-évaluation, contributeurs
├── TP5/                     sujet, auto-évaluation, contributeurs
├── interpreteur/
│   ├── src/
│   │   ├── repl.c           boucle et table de commandes
│   │   ├── lexer.c/.h       analyse lexicale
│   │   ├── parseur.c/.h     parseur simple du TP3
│   │   ├── evaluation.c/.h  évaluateur simple du TP3
│   │   ├── postfixe.c/.h    Shunting-Yard et évaluation RPN
│   │   ├── symboles.c/.h    table de symboles typée
│   │   └── lambda.c/.h      expressions lambda
│   ├── Makefile
│   └── README.md
├── tests/                   framework maison, tests unitaires et scripts
├── docs/                    notes d'implémentation TP1 à TP5
├── .github/workflows/ci.yml CI GitHub Actions
├── Makefile                 build et tests globaux
├── LICENSE                  GPLv3
└── README.md
```

---

## Documentation

- [TP1 — Bases du C](docs/TP1-BASES.md)
- [TP2 — Chaîne de compilation](docs/TP2-CHAINE-COMPILATION.md)
- [TP3 — Architecture de l'interpréteur](docs/TP3-INTERPRETEUR.md)
- [TP4 — Expressions postfixées](docs/TP4-POSTFIXE.md)
- [TP5 — Variables et lambda](docs/TP5-VARIABLES-LAMBDA.md)
- [Synthèse C du TP2](TP2/src/programmation_C.md)

---

## Crédits et licence

- **Squelette, énoncés et interfaces** : John Samuel, CPE Lyon
  ([`johnsamuelwrites/PLP`](https://github.com/johnsamuelwrites/PLP)).
- **Implémentation, tests et documentation** : [ManuelDavid69](https://github.com/ManuelDavid69).
- **Organisation du rendu** inspirée du dépôt public de
  [Ediz Buba](https://github.com/EdizBuba/PLP), qui a suivi le même cours.

Le code est distribué sous licence **GPLv3** (voir [LICENSE](LICENSE)) ; les documents et sujets
sont sous licence CC-BY-SA, conformément au dépôt d'origine.
