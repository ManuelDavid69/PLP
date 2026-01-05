# TP1 — Bases du langage C

## Objectif

Le TP1 couvre les types, les opérateurs, les structures de contrôle et les entrées/sorties.
Chaque exercice est un programme autonome dans `TP1/src/`.

## 1. Programmes

| Fichier | Exercice | Point clé |
|---|---|---|
| `bonjour.c` | 1.1 | premier `printf`, compilation avec `-Wall -Wextra` |
| `cercle.c` | 1.2 | `double`, constante `PI` portable, validation du rayon |
| `sizeof_types.c` | 1.3 | `sizeof` et format `%zu` |
| `variables.c` | 1.4 | types signés, non signés et flottants, `limits.h` |
| `operateurs.c` | 1.5 | arithmétique, comparaisons et logique |
| `boucles.c` | 1.6 | triangle avec `for` et `while` |
| `controle.c` | 1.7 | filtres, `if`/`else if`/`continue`, compteurs |
| `calculs.c` | 1.8 | `switch`, opérateurs bit à bit, erreurs |
| `binaire.c` | 1.9 | divisions par 2, reste, bits groupés |

## 2. Choix d'implémentation

### Constante π

`M_PI` n'est pas garanti par la norme C. Pour rester portable, chaque fichier concerné définit :

```c
#define PI 3.14159265358979323846
```

### Triangle

Une ligne de hauteur `i` contient `i` symboles :

- `*` sur le bord gauche, le bord droit et la dernière ligne ;
- `#` à l'intérieur ;
- un espace entre les symboles, mais pas après le dernier.

La même fonction d'affichage est appelée par une boucle `for` puis par une boucle `while`.

### Filtres de 1 à 1000

Les conditions se chevauchent (par exemple 8 est divisible par 4 et par 8). Le `else if`
garantit qu'un nombre n'est affiché qu'une fois. Les compteurs utilisent `while` et
`do..while` pour illustrer les trois formes de boucle.

### Calculatrice

Le `switch` traite `+`, `-`, `*`, `/`, `%`, `&`, `|` et `~`. Le second opérande n'est demandé
que pour les opérations binaires. La division et le modulo par zéro sont refusés.

### Binaire

La conversion utilise uniquement les divisions par 2 et les restes, conformément au sujet. Les
bits sont affichés de gauche à droite et groupés par quatre. Le programme accepte aussi des
valeurs en arguments pour les tests :

```bash
./TP1/bin/binaire 0 4096 65536 65535 1024
```

## 3. Validation

```bash
make -C TP1
bash tests/test_tp1.sh
```

Les tests vérifient les sorties des neuf programmes, y compris les cas d'erreur (division par
zéro) et le triangle.
