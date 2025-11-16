/*
 * couleurs.c — Exercice 2.7
 * Stocke 100 couleurs RGBA, puis affiche les couleurs distinctes et leur nombre.
 */

#include <stdio.h>

#define NB_COULEURS 100

struct Couleur {
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;
};

static int couleurs_egales(const struct Couleur *gauche, const struct Couleur *droite)
{
    return gauche->r == droite->r &&
           gauche->g == droite->g &&
           gauche->b == droite->b &&
           gauche->a == droite->a;
}

int main(void)
{
    struct Couleur couleurs[NB_COULEURS];

    for (int i = 0; i < NB_COULEURS; i++) {
        switch (i % 7) {
        case 0:
            couleurs[i] = (struct Couleur){255, 0, 0, 255};
            break;
        case 1:
            couleurs[i] = (struct Couleur){0, 255, 0, 255};
            break;
        case 2:
            couleurs[i] = (struct Couleur){0, 0, 255, 255};
            break;
        case 3:
            couleurs[i] = (struct Couleur){255, 255, 0, 255};
            break;
        case 4:
            couleurs[i] = (struct Couleur){0, 255, 255, 255};
            break;
        case 5:
            couleurs[i] = (struct Couleur){255, 0, 255, 255};
            break;
        default:
            couleurs[i] = (struct Couleur){0, 0, 0, 128};
            break;
        }
    }

    struct Couleur distinctes[NB_COULEURS];
    int occurrences[NB_COULEURS];
    int nb_distinctes = 0;

    for (int i = 0; i < NB_COULEURS; i++) {
        int indice = -1;
        for (int j = 0; j < nb_distinctes; j++) {
            if (couleurs_egales(&couleurs[i], &distinctes[j])) {
                indice = j;
                break;
            }
        }

        if (indice >= 0) {
            occurrences[indice]++;
        } else {
            distinctes[nb_distinctes] = couleurs[i];
            occurrences[nb_distinctes] = 1;
            nb_distinctes++;
        }
    }

    printf("Couleurs distinctes : %d\n\n", nb_distinctes);
    printf("  R   G   B   A  | occurrences\n");
    printf("-----------------+------------\n");
    for (int i = 0; i < nb_distinctes; i++) {
        printf("%3u %3u %3u %3u  | %d\n",
               (unsigned int)distinctes[i].r,
               (unsigned int)distinctes[i].g,
               (unsigned int)distinctes[i].b,
               (unsigned int)distinctes[i].a,
               occurrences[i]);
    }

    return 0;
}
