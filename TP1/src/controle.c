/*
 * controle.c — Exercice 1.7
 * Parcourt les nombres de 1 à 1000 et applique trois filtres.
 * La boucle principale utilise for ; les compteurs utilisent while et do..while.
 */

#include <stdio.h>

static int divisible_par_4_sans_6(int n)
{
    return (n % 4 == 0) && (n % 6 != 0);
}

static int pair_et_divisible_par_8(int n)
{
    return (n % 2 == 0) && (n % 8 == 0);
}

static int divisible_par_5_ou_7_sans_10(int n)
{
    return ((n % 5 == 0) || (n % 7 == 0)) && (n % 10 != 0);
}

int main(void)
{
    printf("Nombres de 1 à 1000 répondant aux conditions :\n\n");

    for (int n = 1; n <= 1000; n++) {
        if (divisible_par_4_sans_6(n)) {
            printf("%d : divisible par 4 mais pas par 6\n", n);
        } else if (pair_et_divisible_par_8(n)) {
            printf("%d : pair et divisible par 8\n", n);
        } else if (divisible_par_5_ou_7_sans_10(n)) {
            printf("%d : divisible par 5 ou 7 mais pas par 10\n", n);
        } else {
            continue;
        }
    }

    int n = 1;
    int total_4_sans_6 = 0;
    while (n <= 1000) {
        if (divisible_par_4_sans_6(n)) {
            total_4_sans_6++;
        }
        n++;
    }

    n = 1;
    int total_pair_8 = 0;
    int total_5_ou_7 = 0;
    do {
        if (pair_et_divisible_par_8(n)) {
            total_pair_8++;
        }
        if (divisible_par_5_ou_7_sans_10(n)) {
            total_5_ou_7++;
        }
        n++;
    } while (n <= 1000);

    printf("\nRésumé :\n");
    printf("  Divisible par 4 mais pas par 6 : %d\n", total_4_sans_6);
    printf("  Pair et divisible par 8        : %d\n", total_pair_8);
    printf("  Divisible par 5 ou 7 sans 10   : %d\n", total_5_ou_7);

    return 0;
}
