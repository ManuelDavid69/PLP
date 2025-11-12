/*
 * erreurs.c — Exercice 2.1 (version corrigée)
 *
 * Le programme d'origine contenait l'erreur suivante :
 *
 *     int tableau[100];
 *     for (int compteur = 0; compteur < sizeof(tableau); compteur++)
 *         tableau[compteur] = tableau[compteur] * 2;
 *
 * `sizeof(tableau)` vaut 400 sur une plateforme où `int` occupe 4 octets :
 * la boucle dépasse la fin du tableau et provoque un « stack smashing ».
 * `gcc -Wall -Wextra` signale en plus la comparaison entre un `int` signé
 * et un `size_t` non signé.
 *
 * Correction : utiliser `size_t` et diviser la taille totale par la taille
 * d'un élément. Le programme ci-dessous est donc sûr et sans avertissement.
 */

#include <stdio.h>

#define TABLE_SIZE 100

int main(void)
{
    int tableau[TABLE_SIZE] = {0};
    const size_t nb_elements = sizeof(tableau) / sizeof(tableau[0]);

    for (size_t compteur = 0; compteur < nb_elements; compteur++) {
        tableau[compteur] = tableau[compteur] * 2;
    }

    printf("%zu éléments parcourus sans dépassement.\n", nb_elements);
    return 0;
}
