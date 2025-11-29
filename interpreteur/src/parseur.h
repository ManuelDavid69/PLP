#ifndef PARSEUR_H
#define PARSEUR_H

#include "lexer.h"

/* Représentation interne d'une expression simple « A op B » (TP3). */
typedef struct {
    double operande_gauche;
    double operande_droite;
    TokenType operation; /* TOKEN_PLUS, TOKEN_MINUS, TOKEN_STAR ou TOKEN_SLASH */
} Expression;

int parse_expression(Lexer *lexer, Expression *expression);

#endif
