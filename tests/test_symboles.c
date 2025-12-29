#include "test_framework.h"

#include "symboles.h"

#include <stdio.h>
#include <string.h>

void test_symboles(void)
{
    Variable *variable = NULL;

    symboles_init();

    VERIFIER_INT(1, symboles_est_nom("x"));
    VERIFIER_INT(1, symboles_est_nom("π"));
    VERIFIER_INT(0, symboles_est_nom("12"));
    VERIFIER_INT(0, symboles_est_nom("x y"));
    VERIFIER_INT(0, symboles_est_nom("x=4"));
    VERIFIER_INT(1, symboles_est_affectation("x = 4"));
    VERIFIER_INT(1, symboles_est_affectation("z = \"Bonjour\""));
    VERIFIER_INT(0, symboles_est_affectation("echo \"a=b\""));

    VERIFIER_INT(SYMBOLE_OK, symboles_definir("x", "4", &variable));
    VERIFIER(variable != NULL);
    VERIFIER_INT(VAR_INT, variable->type);
    VERIFIER_INT(4, variable->valeur.entier);
    VERIFIER_CHAINE("x", variable->name);

    VERIFIER_INT(SYMBOLE_OK, symboles_definir("x", "5", &variable));
    VERIFIER_INT(5, variable->valeur.entier);

    VERIFIER_INT(SYMBOLE_ERR_TYPE, symboles_definir("x", "12.3", &variable));
    VERIFIER_INT(VAR_INT, symboles_chercher("x")->type);
    VERIFIER_INT(5, symboles_chercher("x")->valeur.entier);

    VERIFIER_INT(SYMBOLE_OK, symboles_definir("z", "\"Bonjour\"", &variable));
    VERIFIER_INT(VAR_STRING, variable->type);
    VERIFIER_CHAINE("Bonjour", variable->valeur.chaine);

    VERIFIER_INT(SYMBOLE_OK, symboles_definir("π", "3.14", &variable));
    VERIFIER_INT(VAR_REAL, variable->type);
    VERIFIER_DOUBLE(3.14, variable->valeur.reel, 1e-9);

    VERIFIER_INT(SYMBOLE_ERR_NOM, symboles_definir("1x", "4", &variable));
    VERIFIER_INT(SYMBOLE_ERR_VALEUR, symboles_definir("w", "abc", &variable));
    VERIFIER(symboles_chercher("inconnue") == NULL);

    symboles_init();
    for (int i = 0; i < 128; i++) {
        char nom[16];
        snprintf(nom, sizeof nom, "v%d", i);
        VERIFIER_INT(SYMBOLE_OK, symboles_definir(nom, "1", &variable));
    }
    VERIFIER_INT(SYMBOLE_ERR_PLEIN, symboles_definir("v128", "1", &variable));
}
