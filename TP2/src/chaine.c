/*
 * chaine.c — Exercice 2.4
 * Longueur, copie et concaténation de deux chaînes saisies par l'utilisateur.
 */

#include <stdio.h>
#include <string.h>

#define TAILLE 128

static void lire_ligne(char *buffer, size_t taille)
{
    if (fgets(buffer, (int)taille, stdin) == NULL) {
        buffer[0] = '\0';
        return;
    }

    size_t longueur = strlen(buffer);
    while (longueur > 0 && (buffer[longueur - 1] == '\n' || buffer[longueur - 1] == '\r')) {
        buffer[--longueur] = '\0';
    }
}

int main(void)
{
    char chaine1[TAILLE];
    char chaine2[TAILLE];
    char copie[TAILLE];
    char concatenee[2 * TAILLE];

    printf("Première chaîne : ");
    lire_ligne(chaine1, sizeof chaine1);

    printf("Deuxième chaîne : ");
    lire_ligne(chaine2, sizeof chaine2);

    printf("\nLongueur de \"%s\" : %zu\n", chaine1, strlen(chaine1));
    printf("Longueur de \"%s\" : %zu\n", chaine2, strlen(chaine2));

    strcpy(copie, chaine1);
    printf("Copie de la première chaîne : %s\n", copie);

    strcpy(concatenee, chaine1);
    strcat(concatenee, chaine2);
    printf("Concaténation : %s\n", concatenee);

    return 0;
}
