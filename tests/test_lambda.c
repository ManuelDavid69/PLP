#include "test_framework.h"

#include "lambda.h"
#include "symboles.h"

void test_lambda(void)
{
    Variable *variable = NULL;
    double resultat = 0.0;

    symboles_init();
    symboles_definir("y", "4", &variable);

    VERIFIER_INT(1, is_lambda_expression("(lambda x.x + 2 * x) 3"));
    VERIFIER_INT(1, is_lambda_expression("(lambda x.x + 1"));
    VERIFIER_INT(0, is_lambda_expression("2 + 3"));
    VERIFIER_INT(0, is_lambda_expression("lambda x.x + 1"));

    VERIFIER_INT(1, eval_lambda_expression("(lambda x.x + 2 * x) 3", &resultat));
    VERIFIER_DOUBLE(9.0, resultat, 1e-9);

    VERIFIER_INT(1, eval_lambda_expression("(lambda x.(x + 2) * x) y", &resultat));
    VERIFIER_DOUBLE(24.0, resultat, 1e-9);

    VERIFIER_INT(1, eval_lambda_expression("(lambda x.x + 1) -2", &resultat));
    VERIFIER_DOUBLE(-1.0, resultat, 1e-9);

    VERIFIER_INT(1, eval_lambda_expression("(lambda x.x + y) 3", &resultat));
    VERIFIER_DOUBLE(7.0, resultat, 1e-9);

    VERIFIER_INT(1, eval_lambda_expression("(lambda x.x) 2.5", &resultat));
    VERIFIER_DOUBLE(2.5, resultat, 1e-9);

    VERIFIER_INT(0, eval_lambda_expression("(lambda x.x + 1) w", &resultat));
    VERIFIER_INT(0, eval_lambda_expression("(lambda x.) 3", &resultat));
    VERIFIER_INT(0, eval_lambda_expression("(lambda x.x + 1", &resultat));
    VERIFIER_INT(0, eval_lambda_expression("(lambda x.x + 1) 2 3", &resultat));
    VERIFIER_INT(0, eval_lambda_expression("(lambda x.\"abc\") 3", &resultat));
}
