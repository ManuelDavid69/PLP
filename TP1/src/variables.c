/*
 * variables.c — Exercice 1.4
 * Déclare et affiche des variables représentatives de chaque type de base.
 */

#include <limits.h>
#include <stdio.h>

int main(void)
{
    char c = 'A';
    signed char sc = -100;
    unsigned char uc = UCHAR_MAX;

    short s = -30000;
    unsigned short us = USHRT_MAX;

    int i = -2000000000;
    unsigned int ui = UINT_MAX;

    long int l = -900000000L;
    unsigned long int ul = ULONG_MAX;

    long long int ll = -9000000000000000000LL;
    unsigned long long int ull = ULLONG_MAX;

    float f = -3.14f;
    double d = -2.718281828;
    long double ld = -1.61803398875L;

    printf("Types signés :\n");
    printf("char          : %c (%d)\n", c, (int)c);
    printf("signed char   : %d\n", (int)sc);
    printf("short         : %d\n", (int)s);
    printf("int           : %d\n", i);
    printf("long int      : %ld\n", l);
    printf("long long int : %lld\n", ll);

    printf("\nTypes non signés :\n");
    printf("unsigned char       : %u\n", (unsigned int)uc);
    printf("unsigned short      : %u\n", (unsigned int)us);
    printf("unsigned int        : %u\n", ui);
    printf("unsigned long int   : %lu\n", ul);
    printf("unsigned long long  : %llu\n", ull);

    printf("\nTypes flottants :\n");
    printf("float       : %.2f\n", (double)f);
    printf("double      : %.6f\n", d);
    printf("long double : %.10Lf\n", ld);

    return 0;
}
