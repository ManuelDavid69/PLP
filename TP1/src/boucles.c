/*
 * boucles.c — Exercice 1.6
 * Affiche un triangle rectangle dont les bords sont en '*' et l'intérieur en '#'.
 * Deux versions sont proposées : une avec for, une avec while.
 */

#include <stdio.h>

static void afficher_ligne(int ligne, int taille)
{
    for (int colonne = 1; colonne <= ligne; colonne++) {
        char symbole = (colonne == 1 || colonne == ligne || ligne == taille) ? '*' : '#';
        putchar(symbole);
        if (colonne < ligne) {
            putchar(' ');
        }
    }
    putchar('\n');
}

int main(void)
{
    int taille;

    do {
        printf("Taille du triangle (1 à 9) : ");
        if (scanf("%d", &taille) != 1) {
            fprintf(stderr, "Erreur : la taille doit être un entier.\n");
            return 1;
        }
    } while (taille < 1 || taille >= 10);

    printf("\nVersion avec une boucle for :\n");
    for (int ligne = 1; ligne <= taille; ligne++) {
        afficher_ligne(ligne, taille);
    }

    printf("\nVersion avec une boucle while :\n");
    int ligne = 1;
    while (ligne <= taille) {
        afficher_ligne(ligne, taille);
        ligne++;
    }

    return 0;
}
