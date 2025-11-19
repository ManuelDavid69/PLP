# Programmation en C — synthèse du TP2

Ce document rassemble les notions travaillées dans le TP2 : débogage avec GDB, chaîne de
compilation avec GCC, manipulation des chaînes de caractères, structures et recherche dans
les fichiers.

---

## 1. Débogage avec GDB

### 1.1 Compiler avec les symboles de débogage

Pour que GDB puisse afficher les noms de variables et les numéros de ligne, il faut compiler
avec `-g` et désactiver les optimisations qui réorganisent le code :

```bash
gcc -std=c11 -Wall -Wextra -g -O0 erreurs.c -o erreurs
```

### 1.2 Commandes essentielles

| Commande | Rôle |
|---|---|
| `gdb ./erreurs` | Ouvre le programme dans GDB. |
| `run` ou `r` | Lance le programme. |
| `break fichier.c:ligne` | Pose un point d'arrêt. |
| `next` ou `n` | Exécute la ligne suivante sans entrer dans les fonctions. |
| `step` ou `s` | Entre dans la fonction appelée. |
| `print variable` ou `p variable` | Affiche la valeur d'une variable. |
| `info locals` | Affiche toutes les variables locales. |
| `backtrace` ou `bt` | Affiche la pile d'appels après un plantage. |
| `continue` ou `c` | Reprend jusqu'au prochain point d'arrêt. |
| `quit` | Quitte GDB. |

### 1.3 Le bug de `erreurs.c`

Le code d'origine était :

```c
int tableau[100];

for (int compteur = 0; compteur < sizeof(tableau); compteur++) {
    tableau[compteur] = tableau[compteur] * 2;
}
```

`sizeof(tableau)` vaut `100 * sizeof(int)`, soit **400** sur une plateforme où `int` occupe
4 octets. La boucle écrit donc bien au-delà de l'indice 99 : c'est un dépassement de tableau
(*buffer overflow*), qui provoque généralement un `stack smashing detected`.

Avec `gcc -Wall -Wextra`, le compilateur signale aussi une comparaison entre un entier signé
(`compteur`) et un `size_t` non signé (`sizeof`).

**Correction :**

```c
size_t nb_elements = sizeof(tableau) / sizeof(tableau[0]);
for (size_t compteur = 0; compteur < nb_elements; compteur++) {
    tableau[compteur] = tableau[compteur] * 2;
}
```

Il faut donc donner à `compteur` le type `size_t` et comparer à
`sizeof(tableau) / sizeof(tableau[0])`, pas à `sizeof(tableau)`.

---

## 2. Chaîne de compilation avec GCC

### 2.1 Les quatre étapes

| Étape | Commande | Résultat |
|---|---|---|
| Préprocesseur | `gcc -E source.c -o source.i` | Développe les `#include` et les macros. |
| Compilation | `gcc -S source.i -o source.s` | Produit de l'assembleur. |
| Assemblage | `gcc -c source.s -o source.o` | Produit un fichier objet. |
| Édition des liens | `gcc source.o -o programme` | Produit l'exécutable. |

En pratique, `gcc source.c -o programme` enchaîne les quatre étapes.

### 2.2 Projet multi-fichiers

Le projet `sphere` sépare les responsabilités :

- `sphere.h` : prototypes communs ;
- `surface.c` : `calculer_surface` ;
- `volume.c` : `calculer_volume` ;
- `main.c` : point d'entrée et affichage.

Compilation séparée :

```bash
gcc -std=c11 -Wall -Wextra -c main.c -o main.o
gcc -std=c11 -Wall -Wextra -c surface.c -o surface.o
gcc -std=c11 -Wall -Wextra -c volume.c -o volume.o
gcc main.o surface.o volume.o -o sphere -lm
```

Si seul `volume.c` change, il suffit de recompiler `volume.o` puis de relier les objets :
`main.o` et `surface.o` restent valides. C'est exactement ce que fait un `Makefile` avec ses
dépendances.

### 2.3 Avertissements utiles

```bash
gcc -std=c11 -Wall -Wextra -Wpedantic -Werror ...
```

- `-Wall` active les avertissements courants ;
- `-Wextra` en ajoute d'autres, notamment sur les comparaisons signé/non signé ;
- `-Wpedantic` vérifie la conformité stricte au standard ;
- `-Werror` transforme les avertissements en erreurs, ce qui force un code propre.

---

## 3. Manipulation des chaînes en C

### 3.1 Représentation

Une chaîne C est un tableau de `char` terminé par l'octet nul `'\0'`. La longueur logique ne
compte pas ce terminateur. Il faut toujours réserver un caractère de plus que le texte.

### 3.2 Fonctions de `<string.h>`

| Fonction | Rôle | Point d'attention |
|---|---|---|
| `strlen(s)` | Longueur sans `'\0'`. | Retourne un `size_t`. |
| `strcpy(dest, src)` | Copie. | `dest` doit être assez grand. |
| `strncpy(dest, src, n)` | Copie au plus `n` caractères. | Ne termine pas toujours par `'\0'`. |
| `strcat(dest, src)` | Concatène. | Vérifier la place disponible. |
| `strcmp(a, b)` | Compare lexicographiquement. | Retourne 0 si égal. |
| `strstr(texte, motif)` | Cherche une sous-chaîne. | Retourne `NULL` si absente. |

### 3.3 Lire une ligne proprement

`scanf("%s", ...)` s'arrête au premier espace. Pour lire une phrase complète, on utilise
`fgets`, puis on retire le saut de ligne :

```c
char buffer[128];
if (fgets(buffer, sizeof buffer, stdin) != NULL) {
    size_t n = strlen(buffer);
    while (n > 0 && (buffer[n - 1] == '\n' || buffer[n - 1] == '\r')) {
        buffer[--n] = '\0';
    }
}
```

---

## 4. Structures et recherche dans les fichiers

### 4.1 Structure

```c
struct Etudiant {
    char nom[30];
    char prenom[30];
    char adresse[100];
    float note;
};
```

Un tableau de structures permet de stocker plusieurs enregistrements. Les champs texte sont
copiés avec `strcpy` ou `snprintf` en vérifiant toujours la taille de destination.

### 4.2 Lire un fichier ligne par ligne

```c
FILE *f = fopen("montexte.txt", "r");
if (f == NULL) {
    perror("fopen");
    return 1;
}

char ligne[1024];
while (fgets(ligne, sizeof ligne, f) != NULL) {
    /* traiter la ligne */
}
fclose(f);
```

### 4.3 Compter les occurrences d'une phrase

```c
int compter_occurrences(const char *ligne, const char *phrase)
{
    size_t longueur = strlen(phrase);
    int total = 0;
    const char *position = ligne;

    while ((position = strstr(position, phrase)) != NULL) {
        total++;
        position += longueur; /* occurrences non chevauchantes */
    }
    return total;
}
```

Pour des occurrences chevauchantes, on avancerait de `position++` au lieu de
`position += longueur`.

### 4.4 Recherche sans fonction de bibliothèque

L'exercice 2.8 demande une recherche sans `strcmp` ni `strstr`. On compare les caractères un
par un jusqu'au terminateur :

```c
int phrases_egales(const char *a, const char *b)
{
    int i = 0;
    while (a[i] != '\0' && b[i] != '\0') {
        if (a[i] != b[i]) return 0;
        i++;
    }
    return a[i] == b[i];
}
```

---

## 5. Bilan

- GDB permet de localiser un dépassement de tableau et de suivre l'état des variables.
- La compilation séparée explique pourquoi un `Makefile` ne recompile que les fichiers modifiés.
- Les chaînes C demandent une gestion explicite de la mémoire et du terminateur `'\0'`.
- Les structures et `fgets` suffisent pour construire une petite base de données ou rechercher
  des phrases dans un fichier.
- La vérification systématique des entrées et des tailles évite la majorité des bugs.
