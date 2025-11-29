#ifndef LEXER_H
#define LEXER_H

#include <stddef.h>

typedef enum {
    TOKEN_NUMBER,
    TOKEN_IDENTIFIER,
    TOKEN_STRING,
    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_STAR,
    TOKEN_SLASH,
    TOKEN_LPAREN,
    TOKEN_RPAREN,
    TOKEN_DOT,
    TOKEN_EQUAL,
    TOKEN_END,
    TOKEN_ERROR
} TokenType;

typedef struct {
    TokenType type;
    double number;     /* valeur si type == TOKEN_NUMBER */
    char text[128];    /* texte du jeton (identifiant, chaîne, opérateur) */
} Token;

typedef struct {
    const char *input;
    size_t pos;
} Lexer;

void lexer_init(Lexer *lexer, const char *input);
Token lexer_next_token(Lexer *lexer);
const char *token_type_name(TokenType type);

#endif
