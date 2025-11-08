/*
 * binaire.c — Exercice 1.9
 * Affiche la représentation binaire d'un entier en utilisant les divisions par 2.
 * Sans argument, le programme demande une valeur ; avec des arguments, il les traite
 * toutes, ce qui facilite les tests (0, 4096, 65536, 65535, 1024).
 */

#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

static void afficher_binaire(unsigned int valeur)
{
    unsigned int bits[32];
    int nb_bits = 0;

    if (valeur == 0) {
        bits[nb_bits++] = 0;
    } else {
        unsigned int reste = valeur;
        while (reste > 0) {
            bits[nb_bits++] = reste % 2;
            reste /= 2;
        }
    }

    printf("%u en binaire : ", valeur);
    for (int i = nb_bits - 1; i >= 0; i--) {
        printf("%u", bits[i]);
        if (i > 0 && i % 4 == 0) {
            putchar(' ');
        }
    }
    putchar('\n');
}

int main(int argc, char *argv[])
{
    if (argc > 1) {
        for (int i = 1; i < argc; i++) {
            char *fin = NULL;
            errno = 0;
            unsigned long valeur = strtoul(argv[i], &fin, 10);
            if (errno == ERANGE || fin == argv[i] || *fin != '\0' || valeur > UINT_MAX) {
                fprintf(stderr, "Erreur : valeur invalide '%s'.\n", argv[i]);
                return 1;
            }
            afficher_binaire((unsigned int)valeur);
        }
        return 0;
    }

    unsigned int valeur;
    printf("Entier positif à convertir : ");
    if (scanf("%u", &valeur) != 1) {
        fprintf(stderr, "Erreur : la valeur doit être un entier positif.\n");
        return 1;
    }

    afficher_binaire(valeur);
    return 0;
}
