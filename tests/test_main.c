#include "test_framework.h"

#include <math.h>
#include <stdio.h>
#include <string.h>

int tests_executes = 0;
int tests_echoues = 0;

void test_verifier_bool(const char *fichier, int ligne, const char *texte, int condition)
{
    tests_executes++;
    if (!condition) {
        tests_echoues++;
        fprintf(stderr, "ÉCHEC %s:%d : %s\n", fichier, ligne, texte);
    }
}

void test_verifier_int(const char *fichier, int ligne, const char *texte,
                       long long attendu, long long obtenu)
{
    tests_executes++;
    if (attendu != obtenu) {
        tests_echoues++;
        fprintf(stderr, "ÉCHEC %s:%d : %s (attendu %lld, obtenu %lld)\n",
                fichier, ligne, texte, attendu, obtenu);
    }
}

void test_verifier_double(const char *fichier, int ligne, const char *texte,
                          double attendu, double obtenu, double tolerance)
{
    tests_executes++;
    if (fabs(attendu - obtenu) > tolerance) {
        tests_echoues++;
        fprintf(stderr, "ÉCHEC %s:%d : %s (attendu %.10g, obtenu %.10g)\n",
                fichier, ligne, texte, attendu, obtenu);
    }
}

void test_verifier_chaine(const char *fichier, int ligne, const char *texte,
                          const char *attendu, const char *obtenu)
{
    tests_executes++;
    if (attendu == NULL || obtenu == NULL || strcmp(attendu, obtenu) != 0) {
        tests_echoues++;
        fprintf(stderr, "ÉCHEC %s:%d : %s (attendu \"%s\", obtenu \"%s\")\n",
                fichier, ligne, texte,
                attendu == NULL ? "(null)" : attendu,
                obtenu == NULL ? "(null)" : obtenu);
    }
}

void test_lexer(void);
void test_parseur(void);
void test_evaluation(void);

int main(void)
{
    test_lexer();
    test_parseur();
    test_evaluation();

    printf("\n%d vérification(s), %d échec(s).\n", tests_executes, tests_echoues);
    return tests_echoues == 0 ? 0 : 1;
}
