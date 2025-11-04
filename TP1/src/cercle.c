/*
 * cercle.c — Exercice 1.2
 * Calcule l'aire et le périmètre d'un cercle à partir de son rayon.
 */

#include <stdio.h>

#define PI 3.14159265358979323846

int main(void)
{
    double rayon;

    printf("Rayon du cercle : ");
    if (scanf("%lf", &rayon) != 1) {
        fprintf(stderr, "Erreur : le rayon doit être un nombre.\n");
        return 1;
    }

    if (rayon < 0.0) {
        fprintf(stderr, "Erreur : le rayon ne peut pas être négatif.\n");
        return 1;
    }

    printf("Aire = %.2f\n", PI * rayon * rayon);
    printf("Périmètre = %.2f\n", 2.0 * PI * rayon);

    return 0;
}
