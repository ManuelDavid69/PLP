#include "lambda.h"

#include "lexer.h"
#include "postfixe.h"
#include "symboles.h"

#include <ctype.h>
#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static const char *sauter_espaces(const char *texte)
{
    while (*texte != '\0' && isspace((unsigned char)*texte)) {
        texte++;
    }
    return texte;
}

static int mot_insensible_casse(const char *texte, const char *mot)
{
    while (*mot != '\0') {
        if (tolower((unsigned char)*texte) != tolower((unsigned char)*mot)) {
            return 0;
        }
        texte++;
        mot++;
    }
    return 1;
}

static void supprimer_espaces_extremes(char *texte)
{
    char *debut = texte;
    while (*debut != '\0' && isspace((unsigned char)*debut)) {
        debut++;
    }

    if (*debut == '\0') {
        texte[0] = '\0';
        return;
    }

    char *fin = debut + strlen(debut) - 1;
    while (fin > debut && isspace((unsigned char)*fin)) {
        *fin = '\0';
        fin--;
    }

    memmove(texte, debut, strlen(debut) + 1);
}

static int ajouter_morceau(char *destination, size_t taille, size_t *position, const char *texte)
{
    const size_t longueur = strlen(texte);

    if (*position + longueur + 2 > taille) {
        return 0;
    }

    memcpy(destination + *position, texte, longueur);
    *position += longueur;
    destination[*position] = ' ';
    (*position)++;
    destination[*position] = '\0';
    return 1;
}

int is_lambda_expression(const char *ligne)
{
    if (ligne == NULL) {
        return 0;
    }

    const char *curseur = sauter_espaces(ligne);
    if (*curseur != '(') {
        return 0;
    }
    curseur++;

    curseur = sauter_espaces(curseur);
    if (!mot_insensible_casse(curseur, "lambda")) {
        return 0;
    }
    curseur += 6;

    return strchr(curseur, '.') != NULL;
}

int eval_lambda_expression(const char *ligne, double *resultat)
{
    char copie[1024];
    char parametre[128];
    char expression[512];
    char argument[256];
    char valeur_argument[64];
    char substituee[1024];

    if (ligne == NULL || resultat == NULL) {
        return 0;
    }

    snprintf(copie, sizeof copie, "%s", ligne);

    const char *curseur = sauter_espaces(copie);
    if (*curseur != '(') {
        printf("Erreur : une expression lambda doit commencer par '('.\n");
        return 0;
    }
    curseur++;

    curseur = sauter_espaces(curseur);
    if (!mot_insensible_casse(curseur, "lambda")) {
        printf("Erreur : le mot-clé 'lambda' est attendu.\n");
        return 0;
    }
    curseur += 6;
    curseur = sauter_espaces(curseur);

    size_t i = 0;
    while (*curseur != '\0' && *curseur != ' ' && *curseur != '.' && i + 1 < sizeof parametre) {
        parametre[i++] = *curseur++;
    }
    parametre[i] = '\0';

    if (!symboles_est_nom(parametre)) {
        printf("Erreur : nom de paramètre lambda invalide.\n");
        return 0;
    }

    curseur = sauter_espaces(curseur);
    if (*curseur != '.') {
        printf("Erreur : un point est attendu après le paramètre lambda.\n");
        return 0;
    }
    curseur++;
    curseur = sauter_espaces(curseur);

    const char *debut_expression = curseur;
    int profondeur = 1;
    while (*curseur != '\0') {
        if (*curseur == '(') {
            profondeur++;
        } else if (*curseur == ')') {
            profondeur--;
            if (profondeur == 0) {
                break;
            }
        }
        curseur++;
    }

    if (*curseur != ')') {
        printf("Erreur : parenthèse fermante manquante dans l'expression lambda.\n");
        return 0;
    }

    const size_t longueur_expression = (size_t)(curseur - debut_expression);
    if (longueur_expression == 0 || longueur_expression >= sizeof expression) {
        printf("Erreur : expression lambda vide ou trop longue.\n");
        return 0;
    }

    memcpy(expression, debut_expression, longueur_expression);
    expression[longueur_expression] = '\0';
    supprimer_espaces_extremes(expression);

    curseur++;
    curseur = sauter_espaces(curseur);

    size_t j = 0;
    while (*curseur != '\0' && !isspace((unsigned char)*curseur) && j + 1 < sizeof argument) {
        argument[j++] = *curseur++;
    }
    argument[j] = '\0';

    if (argument[0] == '\0') {
        printf("Erreur : argument manquant après l'expression lambda.\n");
        return 0;
    }
    if (*sauter_espaces(curseur) != '\0') {
        printf("Erreur : argument lambda invalide.\n");
        return 0;
    }

    if (argument[0] == '"') {
        printf("Erreur : une lambda ne peut pas prendre une chaîne de caractères.\n");
        return 0;
    }

    if (symboles_est_nom(argument)) {
        Variable *variable = symboles_chercher(argument);
        if (variable == NULL) {
            printf("Erreur : la variable %s n'est pas définie\n", argument);
            return 0;
        }
        if (variable->type == VAR_STRING) {
            printf("Erreur : une lambda ne peut pas prendre une chaîne de caractères.\n");
            return 0;
        }
        if (variable->type == VAR_INT) {
            snprintf(valeur_argument, sizeof valeur_argument, "%lld", variable->valeur.entier);
        } else {
            snprintf(valeur_argument, sizeof valeur_argument, "%.17g", variable->valeur.reel);
        }
    } else {
        errno = 0;
        char *fin = NULL;
        const double valeur = strtod(argument, &fin);
        if (fin == argument || *fin != '\0' || errno == ERANGE || !isfinite(valeur)) {
            printf("Erreur : argument lambda invalide.\n");
            return 0;
        }
        snprintf(valeur_argument, sizeof valeur_argument, "%.17g", valeur);
    }

    Lexer lexer;
    lexer_init(&lexer, expression);

    size_t position = 0;
    substituee[0] = '\0';

    for (;;) {
        Token jeton = lexer_next_token(&lexer);

        if (jeton.type == TOKEN_END) {
            break;
        }

        if (jeton.type == TOKEN_NUMBER) {
            if (!ajouter_morceau(substituee, sizeof substituee, &position, jeton.text)) {
                printf("Erreur : expression lambda trop longue.\n");
                return 0;
            }
            continue;
        }

        if (jeton.type == TOKEN_IDENTIFIER) {
            if (strcmp(jeton.text, parametre) == 0) {
                if (!ajouter_morceau(substituee, sizeof substituee, &position, valeur_argument)) {
                    printf("Erreur : expression lambda trop longue.\n");
                    return 0;
                }
                continue;
            }

            Variable *variable = symboles_chercher(jeton.text);
            if (variable == NULL) {
                printf("Erreur : la variable %s n'est pas définie\n", jeton.text);
                return 0;
            }
            if (variable->type == VAR_STRING) {
                printf("Erreur : la variable %s est une chaîne et ne peut pas être utilisée ici.\n",
                       jeton.text);
                return 0;
            }

            char valeur[64];
            if (variable->type == VAR_INT) {
                snprintf(valeur, sizeof valeur, "%lld", variable->valeur.entier);
            } else {
                snprintf(valeur, sizeof valeur, "%.17g", variable->valeur.reel);
            }

            if (!ajouter_morceau(substituee, sizeof substituee, &position, valeur)) {
                printf("Erreur : expression lambda trop longue.\n");
                return 0;
            }
            continue;
        }

        if (jeton.type == TOKEN_PLUS || jeton.type == TOKEN_MINUS ||
            jeton.type == TOKEN_STAR || jeton.type == TOKEN_SLASH ||
            jeton.type == TOKEN_LPAREN || jeton.type == TOKEN_RPAREN) {
            if (!ajouter_morceau(substituee, sizeof substituee, &position, jeton.text)) {
                printf("Erreur : expression lambda trop longue.\n");
                return 0;
            }
            continue;
        }

        printf("Erreur : expression lambda invalide.\n");
        return 0;
    }

    if (position > 0 && substituee[position - 1] == ' ') {
        substituee[position - 1] = '\0';
    }

    return evaluate_infix(substituee, resultat);
}
