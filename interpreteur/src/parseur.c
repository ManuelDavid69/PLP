#include "parseur.h"

#include <stdio.h>

static int est_operateur(TokenType type)
{
    return type == TOKEN_PLUS ||
           type == TOKEN_MINUS ||
           type == TOKEN_STAR ||
           type == TOKEN_SLASH;
}

int parse_expression(Lexer *lexer, Expression *expression)
{
    Token jeton = lexer_next_token(lexer);

    if (jeton.type != TOKEN_NUMBER) {
        fprintf(stderr, "Erreur de syntaxe : un nombre était attendu au début de l'expression.\n");
        return 0;
    }
    expression->operande_gauche = jeton.number;

    jeton = lexer_next_token(lexer);
    if (!est_operateur(jeton.type)) {
        fprintf(stderr, "Erreur de syntaxe : un opérateur +, -, * ou / était attendu.\n");
        return 0;
    }
    expression->operation = jeton.type;

    jeton = lexer_next_token(lexer);
    if (jeton.type != TOKEN_NUMBER) {
        fprintf(stderr, "Erreur de syntaxe : un second nombre était attendu.\n");
        return 0;
    }
    expression->operande_droite = jeton.number;

    jeton = lexer_next_token(lexer);
    if (jeton.type != TOKEN_END) {
        fprintf(stderr, "Erreur de syntaxe : des caractères inattendus suivent l'expression.\n");
        return 0;
    }

    return 1;
}
