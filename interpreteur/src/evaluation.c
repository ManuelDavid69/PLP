#include "evaluation.h"

#include <stdio.h>

int evaluer_expression(const Expression *expression, double *resultat)
{
    if (expression == NULL || resultat == NULL) {
        return 0;
    }

    switch (expression->operation) {
    case TOKEN_PLUS:
        *resultat = expression->operande_gauche + expression->operande_droite;
        return 1;

    case TOKEN_MINUS:
        *resultat = expression->operande_gauche - expression->operande_droite;
        return 1;

    case TOKEN_STAR:
        *resultat = expression->operande_gauche * expression->operande_droite;
        return 1;

    case TOKEN_SLASH:
        if (expression->operande_droite == 0.0) {
            fprintf(stderr, "Erreur : division par zéro.\n");
            return 0;
        }
        *resultat = expression->operande_gauche / expression->operande_droite;
        return 1;

    default:
        fprintf(stderr, "Erreur : opérateur inconnu.\n");
        return 0;
    }
}
