#ifndef POSTFIXE_H
#define POSTFIXE_H

#include <stddef.h>

/* Convertit une expression infixe en notation postfixée. */
int infix_to_postfix(const char *infixe, char *postfixe, size_t taille);

#endif
