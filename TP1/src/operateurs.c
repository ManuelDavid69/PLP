/*
 * operateurs.c — Exercice 1.5
 * Illustre les opérateurs arithmétiques, de comparaison et logiques.
 */

#include <stdio.h>

int main(void)
{
    int a = 16;
    int b = 3;

    printf("Opérateurs arithmétiques :\n");
    printf("a = %d, b = %d\n", a, b);
    printf("Addition       : %d + %d = %d\n", a, b, a + b);
    printf("Soustraction   : %d - %d = %d\n", a, b, a - b);
    printf("Multiplication : %d * %d = %d\n", a, b, a * b);
    printf("Division       : %d / %d = %d\n", a, b, a / b);
    printf("Modulo         : %d %% %d = %d\n", a, b, a % b);

    printf("\nComparaisons :\n");
    printf("a == b : %d\n", a == b);
    printf("a != b : %d\n", a != b);
    printf("a >  b : %d\n", a > b);
    printf("a <  b : %d\n", a < b);
    printf("a >= b : %d\n", a >= b);
    printf("a <= b : %d\n", a <= b);

    printf("\nOpérateurs logiques :\n");
    printf("(a > 0) && (b > 0) : %d\n", (a > 0) && (b > 0));
    printf("(a < 0) || (b > 0) : %d\n", (a < 0) || (b > 0));
    printf("!(a == b)          : %d\n", !(a == b));

    return 0;
}
