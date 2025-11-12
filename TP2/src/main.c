/*
 * main.c — Exercice 2.3
 * Programme principal du projet multi-fichiers « sphere ».
 */

#include <stdio.h>
#include <stdlib.h>

#include "sphere.h"

int main(int argc, char *argv[])
{
    float rayon = 5.0f;

    if (argc > 1) {
        char *fin = NULL;
        float valeur = strtof(argv[1], &fin);
        if (fin == argv[1] || *fin != '\0' || valeur < 0.0f) {
            fprintf(stderr, "Erreur : rayon invalide '%s'.\n", argv[1]);
            return 1;
        }
        rayon = valeur;
    }

    printf("Le volume de la sphère de rayon %.2f est %.2f\n",
           (double)rayon, (double)calculer_volume(rayon));
    printf("La surface de la sphère de rayon %.2f est %.2f\n",
           (double)rayon, (double)calculer_surface(rayon));

    return 0;
}
