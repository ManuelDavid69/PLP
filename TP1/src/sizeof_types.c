/*
 * sizeof_types.c — Exercice 1.3
 * Affiche la taille en octets des principaux types de base du C.
 */

#include <stdio.h>

int main(void)
{
    printf("Tailles des types de base en C :\n\n");

    printf("char                : %zu octet(s)\n", sizeof(char));
    printf("signed char         : %zu octet(s)\n", sizeof(signed char));
    printf("unsigned char       : %zu octet(s)\n", sizeof(unsigned char));
    printf("short               : %zu octet(s)\n", sizeof(short));
    printf("unsigned short      : %zu octet(s)\n", sizeof(unsigned short));
    printf("int                 : %zu octet(s)\n", sizeof(int));
    printf("unsigned int        : %zu octet(s)\n", sizeof(unsigned int));
    printf("long int            : %zu octet(s)\n", sizeof(long int));
    printf("unsigned long int   : %zu octet(s)\n", sizeof(unsigned long int));
    printf("long long int       : %zu octet(s)\n", sizeof(long long int));
    printf("unsigned long long  : %zu octet(s)\n", sizeof(unsigned long long int));
    printf("float               : %zu octet(s)\n", sizeof(float));
    printf("double              : %zu octet(s)\n", sizeof(double));
    printf("long double         : %zu octet(s)\n", sizeof(long double));

    return 0;
}
