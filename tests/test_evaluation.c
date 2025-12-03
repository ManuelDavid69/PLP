#include "test_framework.h"

#include "evaluation.h"

void test_evaluation(void)
{
    Expression expression;
    double resultat = 0.0;

    expression.operande_gauche = 8.0;
    expression.operande_droite = 2.0;

    expression.operation = TOKEN_PLUS;
    VERIFIER_INT(1, evaluer_expression(&expression, &resultat));
    VERIFIER_DOUBLE(10.0, resultat, 1e-9);

    expression.operation = TOKEN_MINUS;
    VERIFIER_INT(1, evaluer_expression(&expression, &resultat));
    VERIFIER_DOUBLE(6.0, resultat, 1e-9);

    expression.operation = TOKEN_STAR;
    VERIFIER_INT(1, evaluer_expression(&expression, &resultat));
    VERIFIER_DOUBLE(16.0, resultat, 1e-9);

    expression.operation = TOKEN_SLASH;
    VERIFIER_INT(1, evaluer_expression(&expression, &resultat));
    VERIFIER_DOUBLE(4.0, resultat, 1e-9);

    expression.operande_droite = 0.0;
    VERIFIER_INT(0, evaluer_expression(&expression, &resultat));

    expression.operation = TOKEN_NUMBER;
    VERIFIER_INT(0, evaluer_expression(&expression, &resultat));
}
