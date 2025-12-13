#ifndef POSTFIXE_H
#define POSTFIXE_H

#include <stddef.h>

/* Convertit une expression infixe en notation postfixée. */
int infix_to_postfix(const char *infixe, char *postfixe, size_t taille);

/* Évalue une expression postfixée avec une pile d'opérandes. */
int eval_postfix(const char *postfixe, double *resultat);

/* Convertit puis évalue une expression infixe. */
int evaluate_infix(const char *infixe, double *resultat);

/* Indique si une ligne ressemble à une expression arithmétique. */
int is_arithmetic_expression(const char *ligne);

#endif
