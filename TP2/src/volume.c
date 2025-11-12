/*
 * volume.c — Exercice 2.3
 * Calcul du volume d'une sphère : (4/3) × π × r³.
 */

#include "sphere.h"

#define PI 3.14159265358979323846

float calculer_volume(float rayon)
{
    return (float)((4.0 / 3.0) * PI * rayon * rayon * rayon);
}
