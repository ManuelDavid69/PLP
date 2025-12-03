#include "test_framework.h"

#include "evaluation.h"
#include "lexer.h"
#include "parseur.h"

static double evaluer(const char *texte, int *succes)
{
    Lexer lexer;
    Expression expression;
    double resultat = 0.0;

    lexer_init(&lexer, texte);
    *succes = parse_expression(&lexer, &expression) &&
              evaluer_expression(&expression, &resultat);
    return resultat;
}

void test_parseur(void)
{
    Lexer lexer;
    Expression expression;
    int succes;
    double resultat;

    lexer_init(&lexer, "2 + 3");
    VERIFIER_INT(1, parse_expression(&lexer, &expression));
    VERIFIER_DOUBLE(2.0, expression.operande_gauche, 1e-9);
    VERIFIER_INT(TOKEN_PLUS, expression.operation);
    VERIFIER_DOUBLE(3.0, expression.operande_droite, 1e-9);

    resultat = evaluer("2 + 3", &succes);
    VERIFIER_INT(1, succes);
    VERIFIER_DOUBLE(5.0, resultat, 1e-9);

    resultat = evaluer("10 / 4", &succes);
    VERIFIER_INT(1, succes);
    VERIFIER_DOUBLE(2.5, resultat, 1e-9);

    resultat = evaluer("1.2 * 4.0", &succes);
    VERIFIER_INT(1, succes);
    VERIFIER_DOUBLE(4.8, resultat, 1e-9);

    resultat = evaluer("7 - 10", &succes);
    VERIFIER_INT(1, succes);
    VERIFIER_DOUBLE(-3.0, resultat, 1e-9);

    lexer_init(&lexer, "2 +");
    VERIFIER_INT(0, parse_expression(&lexer, &expression));

    lexer_init(&lexer, "2 + 3 x");
    VERIFIER_INT(0, parse_expression(&lexer, &expression));

    lexer_init(&lexer, "x + 3");
    VERIFIER_INT(0, parse_expression(&lexer, &expression));

    lexer_init(&lexer, "(2 + 3)");
    VERIFIER_INT(0, parse_expression(&lexer, &expression));
}
