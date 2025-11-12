/*
 * surface.c — Exercice 2.3
 * Calcul de la surface d'une sphère : 4 × π × r².
 */

#include "sphere.h"

#define PI 3.14159265358979323846

float calculer_surface(float rayon)
{
    return (float)(4.0 * PI * rayon * rayon);
}
