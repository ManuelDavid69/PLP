/*
 * aire.c — Exercice 2.2
 * Illustre la chaîne de compilation : une fonction, un appel et un affichage.
 */

#include <stdio.h>

#define PI 3.14159265358979323846

static float calculer_aire(float rayon)
{
    return (float)(PI * rayon * rayon);
}

int main(void)
{
    float rayon = 5.0f;
    float aire = calculer_aire(rayon);

    printf("L'aire du cercle de rayon %.2f est %.2f\n", (double)rayon, (double)aire);
    return 0;
}
