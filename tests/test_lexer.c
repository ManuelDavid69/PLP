#include "test_framework.h"

#include "lexer.h"

#include <string.h>

void test_lexer(void)
{
    Lexer lexer;
    Token jeton;

    lexer_init(&lexer, "12 + 3.5 * (4 - 2) / 8");

    jeton = lexer_next_token(&lexer);
    VERIFIER_INT(TOKEN_NUMBER, jeton.type);
    VERIFIER_DOUBLE(12.0, jeton.number, 1e-9);

    jeton = lexer_next_token(&lexer);
    VERIFIER_INT(TOKEN_PLUS, jeton.type);

    jeton = lexer_next_token(&lexer);
    VERIFIER_INT(TOKEN_NUMBER, jeton.type);
    VERIFIER_DOUBLE(3.5, jeton.number, 1e-9);

    jeton = lexer_next_token(&lexer);
    VERIFIER_INT(TOKEN_STAR, jeton.type);

    jeton = lexer_next_token(&lexer);
    VERIFIER_INT(TOKEN_LPAREN, jeton.type);

    jeton = lexer_next_token(&lexer);
    VERIFIER_INT(TOKEN_NUMBER, jeton.type);
    VERIFIER_DOUBLE(4.0, jeton.number, 1e-9);

    jeton = lexer_next_token(&lexer);
    VERIFIER_INT(TOKEN_MINUS, jeton.type);

    jeton = lexer_next_token(&lexer);
    VERIFIER_INT(TOKEN_NUMBER, jeton.type);
    VERIFIER_DOUBLE(2.0, jeton.number, 1e-9);

    jeton = lexer_next_token(&lexer);
    VERIFIER_INT(TOKEN_RPAREN, jeton.type);

    jeton = lexer_next_token(&lexer);
    VERIFIER_INT(TOKEN_SLASH, jeton.type);

    jeton = lexer_next_token(&lexer);
    VERIFIER_INT(TOKEN_NUMBER, jeton.type);
    VERIFIER_DOUBLE(8.0, jeton.number, 1e-9);

    jeton = lexer_next_token(&lexer);
    VERIFIER_INT(TOKEN_END, jeton.type);

    lexer_init(&lexer, "\"Bonjour le monde\"");
    jeton = lexer_next_token(&lexer);
    VERIFIER_INT(TOKEN_STRING, jeton.type);
    VERIFIER_CHAINE("Bonjour le monde", jeton.text);

    lexer_init(&lexer, "x = 4");
    jeton = lexer_next_token(&lexer);
    VERIFIER_INT(TOKEN_IDENTIFIER, jeton.type);
    VERIFIER_CHAINE("x", jeton.text);
    jeton = lexer_next_token(&lexer);
    VERIFIER_INT(TOKEN_EQUAL, jeton.type);

    lexer_init(&lexer, "π = 3.14");
    jeton = lexer_next_token(&lexer);
    VERIFIER_INT(TOKEN_IDENTIFIER, jeton.type);
    VERIFIER_CHAINE("π", jeton.text);

    lexer_init(&lexer, "1.2.3");
    jeton = lexer_next_token(&lexer);
    VERIFIER_INT(TOKEN_ERROR, jeton.type);

    lexer_init(&lexer, ".5 + 2.");
    jeton = lexer_next_token(&lexer);
    VERIFIER_INT(TOKEN_NUMBER, jeton.type);
    VERIFIER_DOUBLE(0.5, jeton.number, 1e-9);
    jeton = lexer_next_token(&lexer);
    VERIFIER_INT(TOKEN_PLUS, jeton.type);
    jeton = lexer_next_token(&lexer);
    VERIFIER_INT(TOKEN_NUMBER, jeton.type);
    VERIFIER_DOUBLE(2.0, jeton.number, 1e-9);

    lexer_init(&lexer, "@");
    jeton = lexer_next_token(&lexer);
    VERIFIER_INT(TOKEN_ERROR, jeton.type);
}
