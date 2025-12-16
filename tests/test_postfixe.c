#include "test_framework.h"

#include "postfixe.h"

#include <string.h>

void test_postfixe(void)
{
    char sortie[256];
    double resultat = 0.0;

    VERIFIER_INT(1, infix_to_postfix("3 + 4 * 5", sortie, sizeof sortie));
    VERIFIER_CHAINE("3 4 5 * +", sortie);

    VERIFIER_INT(1, infix_to_postfix("(3 + 4) * 5", sortie, sizeof sortie));
    VERIFIER_CHAINE("3 4 + 5 *", sortie);

    VERIFIER_INT(1, infix_to_postfix("2 * (3 + 4) * 5", sortie, sizeof sortie));
    VERIFIER_CHAINE("2 3 4 + * 5 *", sortie);

    VERIFIER_INT(1, infix_to_postfix("-3 + 5", sortie, sizeof sortie));
    VERIFIER_CHAINE("3 u 5 +", sortie);

    VERIFIER_INT(1, infix_to_postfix("-(3 + 4)", sortie, sizeof sortie));
    VERIFIER_CHAINE("3 4 + u", sortie);

    VERIFIER_INT(0, infix_to_postfix("3 + (4 * 5", sortie, sizeof sortie));
    VERIFIER_INT(0, infix_to_postfix("3 + 4)", sortie, sizeof sortie));
    VERIFIER_INT(0, infix_to_postfix("()", sortie, sizeof sortie));
    VERIFIER_INT(0, infix_to_postfix("2 +", sortie, sizeof sortie));
    VERIFIER_INT(0, infix_to_postfix("3 + 4 * 5", sortie, 3));

    VERIFIER_INT(1, evaluate_infix("3 + 4 * 5", &resultat));
    VERIFIER_DOUBLE(23.0, resultat, 1e-9);

    VERIFIER_INT(1, evaluate_infix("(3 + 4) * 5", &resultat));
    VERIFIER_DOUBLE(35.0, resultat, 1e-9);

    VERIFIER_INT(1, evaluate_infix("1.2 * 4.0", &resultat));
    VERIFIER_DOUBLE(4.8, resultat, 1e-9);

    VERIFIER_INT(1, evaluate_infix("10 / 4", &resultat));
    VERIFIER_DOUBLE(2.5, resultat, 1e-9);

    VERIFIER_INT(1, evaluate_infix("-3 + 5", &resultat));
    VERIFIER_DOUBLE(2.0, resultat, 1e-9);

    VERIFIER_INT(1, evaluate_infix("2 * -3", &resultat));
    VERIFIER_DOUBLE(-6.0, resultat, 1e-9);

    VERIFIER_INT(1, evaluate_infix("3 - -2", &resultat));
    VERIFIER_DOUBLE(5.0, resultat, 1e-9);

    VERIFIER_INT(0, evaluate_infix("10 / 0", &resultat));
    VERIFIER_INT(0, evaluate_infix("2 +", &resultat));

    VERIFIER_INT(1, is_arithmetic_expression("2 + 3"));
    VERIFIER_INT(1, is_arithmetic_expression("(3 + 4) * 5"));
    VERIFIER_INT(0, is_arithmetic_expression("foo"));
    VERIFIER_INT(0, is_arithmetic_expression("x + 2"));
    VERIFIER_INT(0, is_arithmetic_expression(""));
}
