# TP5 — Variables typées et expressions lambda

## Objectif

Le TP5 ajoute deux briques à l'interpréteur :

1. une **table de symboles** typée pour les affectations et les lectures de variables ;
2. un **parseur et évaluateur lambda** de la forme `(lambda x.expression) argument`.

```text
> x = 4
Variable x définie avec la valeur 4 (entier)

> x
4

> (lambda x.x + 2 * x) 3
9
```

## 1. Table de symboles

```c
typedef struct {
    char name[128];
    VarType type;
    union {
        long long entier;
        double reel;
        char chaine[256];
    } valeur;
} Variable;
```

La table est un tableau statique de 128 variables. `symboles_chercher()` parcourt les entrées
et compare les noms avec `strcmp`.

### Types et contraintes

| Type | Exemple | Stockage |
|---|---|---|
| `VAR_INT` | `x = 12` | `long long` |
| `VAR_REAL` | `π = 3.14` | `double` |
| `VAR_STRING` | `z = "Bonjour"` | `char[256]` |

Une variable conserve son type : une seconde affectation avec un type différent est refusée.

```text
> x = 4
Variable x définie avec la valeur 4 (entier)
> x = 12.3
Erreur : changement de type non autorisé pour la variable x
```

### Analyse d'une affectation

1. Chercher le premier `=` hors guillemets.
2. Séparer le nom et la valeur, puis supprimer les espaces extrêmes.
3. Valider le nom : non vide, ne commençant pas par un chiffre, sans opérateur ni espace.
4. Analyser la valeur :
   - guillemets → chaîne, avec gestion de `\n`, `\t`, `\"`, `\\` ;
   - pas de `.` ni d'exposant → `strtoll` ;
   - sinon → `strtod`.
5. Vérifier le type existant, puis ajouter ou mettre à jour l'entrée.

Les noms sont comparés octet par octet : les noms UTF-8 comme `π` fonctionnent sans traitement
particulier.

Dans le REPL final, un mot seul qui n'est pas une commande connue est traité comme un nom de
variable : `foo` affiche donc « la variable foo n'est pas définie » plutôt que « commande
inconnue ».

## 2. Expressions lambda

### Syntaxe

```text
(lambda paramètre.expression) argument
```

- `paramètre` : nom de variable valide ;
- `expression` : expression arithmétique du TP4, avec parenthèses ;
- `argument` : nombre ou variable déjà définie.

### Parsing

1. Vérifier le `(`, le mot `lambda` (insensible à la casse) et le point.
2. Lire le nom du paramètre jusqu'à l'espace ou au point.
3. Chercher la parenthèse fermante correspondante en comptant la profondeur des parenthèses.
4. Lire l'argument après la parenthèse fermante ; il doit être unique.

### Substitution

La substitution ne se fait pas avec un `strstr` naïf : le lexer découpe d'abord le corps en
jetons. Un identifiant n'est remplacé que s'il est exactement égal au paramètre.

```text
(lambda x.x + 2 * x) 3
→ 3 + 2 * 3
→ 9
```

Cela évite de remplacer le `x` de `exp` ou de `max` par erreur.

### Argument variable

Si l'argument est un nom, il est cherché dans la table :

```text
> y = 4
> (lambda x.(x + 2) * x) y
24
```

Si l'argument est une chaîne ou une variable non définie, une erreur est affichée.

### Variables libres

Le corps de la lambda peut aussi utiliser des variables déjà définies :

```text
> y = 4
> (lambda x.x + y) 3
7
```

Chaque identifiant libre est résolu dans la table avant l'évaluation.

## 3. Gestion des erreurs

- nom de paramètre invalide ;
- point manquant ;
- parenthèse fermante manquante ;
- corps vide ou trop long ;
- argument manquant ou multiple ;
- argument chaîne de caractères ;
- variable d'argument ou de corps non définie ;
- expression invalide après substitution ;
- division par zéro lors de l'évaluation.

## 4. Validation

```bash
make -C interpreteur
printf 'x = 4\n(lambda x.x + 2 * x) 3\n(lambda x.(x + 2) * x) y\nquit\n' |
    ./interpreteur/interpreteur
make -C tests test
bash tests/test_interpreteur.sh
```

Les tests unitaires couvrent la table de symboles, les types, les erreurs et les lambdas. Le
script d'intégration vérifie le REPL de bout en bout, du TP3 au TP5.
