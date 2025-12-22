#include "symboles.h"

#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_VARIABLES 128

static Variable table[MAX_VARIABLES];
static size_t nombre_variables = 0;

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

void symboles_init(void)
{
    nombre_variables = 0;
    memset(table, 0, sizeof table);
}

Variable *symboles_chercher(const char *nom)
{
    if (nom == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < nombre_variables; i++) {
        if (strcmp(table[i].name, nom) == 0) {
            return &table[i];
        }
    }

    return NULL;
}

int symboles_est_nom(const char *ligne)
{
    if (ligne == NULL) {
        return 0;
    }

    const size_t longueur = strlen(ligne);
    if (longueur == 0 || longueur >= sizeof table[0].name) {
        return 0;
    }

    if (isdigit((unsigned char)ligne[0])) {
        return 0;
    }

    for (size_t i = 0; i < longueur; i++) {
        const unsigned char c = (unsigned char)ligne[i];
        if (c <= ' ' || strchr("=+-*/()[]{}.,;\"", c) != NULL) {
            return 0;
        }
    }

    return 1;
}

int symboles_est_affectation(const char *ligne)
{
    int dans_guillemets = 0;

    if (ligne == NULL) {
        return 0;
    }

    for (const char *curseur = ligne; *curseur != '\0'; curseur++) {
        if (*curseur == '"' && (curseur == ligne || curseur[-1] != '\\')) {
            dans_guillemets = !dans_guillemets;
        } else if (*curseur == '=' && !dans_guillemets) {
            return 1;
        }
    }

    return 0;
}

const char *symboles_nom_type(VarType type)
{
    switch (type) {
    case VAR_INT:
        return "entier";
    case VAR_REAL:
        return "nombre réel";
    case VAR_STRING:
        return "chaîne de caractères";
    default:
        return "inconnu";
    }
}

static StatutSymbole analyser_valeur(const char *brut, Variable *destination)
{
    const size_t longueur = strlen(brut);

    if (longueur == 0) {
        return SYMBOLE_ERR_VALEUR;
    }

    /* Chaîne entre guillemets, avec échappements \n, \t, \" et \\. */
    if (brut[0] == '"') {
        if (longueur < 2 || brut[longueur - 1] != '"') {
            return SYMBOLE_ERR_VALEUR;
        }

        size_t j = 0;
        for (size_t i = 1; i < longueur - 1; i++) {
            char caractere = brut[i];

            if (caractere == '\\' && i + 1 < longueur - 1) {
                i++;
                switch (brut[i]) {
                case 'n':
                    caractere = '\n';
                    break;
                case 't':
                    caractere = '\t';
                    break;
                default:
                    caractere = brut[i];
                    break;
                }
            }

            if (j + 1 >= sizeof destination->valeur.chaine) {
                return SYMBOLE_ERR_VALEUR;
            }
            destination->valeur.chaine[j++] = caractere;
        }

        destination->valeur.chaine[j] = '\0';
        destination->type = VAR_STRING;
        return SYMBOLE_OK;
    }

    int contient_point_ou_exposant = 0;
    for (size_t i = 0; i < longueur; i++) {
        if (brut[i] == '.' || brut[i] == 'e' || brut[i] == 'E') {
            contient_point_ou_exposant = 1;
            break;
        }
    }

    if (!contient_point_ou_exposant) {
        errno = 0;
        char *fin = NULL;
        const long long valeur = strtoll(brut, &fin, 10);

        if (fin == brut || *fin != '\0' || errno == ERANGE) {
            return SYMBOLE_ERR_VALEUR;
        }

        destination->type = VAR_INT;
        destination->valeur.entier = valeur;
        return SYMBOLE_OK;
    }

    errno = 0;
    char *fin = NULL;
    const double valeur = strtod(brut, &fin);

    if (fin == brut || *fin != '\0' || errno == ERANGE) {
        return SYMBOLE_ERR_VALEUR;
    }

    destination->type = VAR_REAL;
    destination->valeur.reel = valeur;
    return SYMBOLE_OK;
}

StatutSymbole symboles_definir(const char *nom, const char *valeur_brute, Variable **resultat)
{
    if (resultat != NULL) {
        *resultat = NULL;
    }

    if (!symboles_est_nom(nom)) {
        return SYMBOLE_ERR_NOM;
    }

    Variable nouvelle;
    memset(&nouvelle, 0, sizeof nouvelle);
    strcpy(nouvelle.name, nom);

    const StatutSymbole statut = analyser_valeur(valeur_brute, &nouvelle);
    if (statut != SYMBOLE_OK) {
        return statut;
    }

    Variable *existante = symboles_chercher(nom);
    if (existante != NULL) {
        if (existante->type != nouvelle.type) {
            return SYMBOLE_ERR_TYPE;
        }
        *existante = nouvelle;
        if (resultat != NULL) {
            *resultat = existante;
        }
        return SYMBOLE_OK;
    }

    if (nombre_variables >= MAX_VARIABLES) {
        return SYMBOLE_ERR_PLEIN;
    }

    table[nombre_variables] = nouvelle;
    if (resultat != NULL) {
        *resultat = &table[nombre_variables];
    }
    nombre_variables++;
    return SYMBOLE_OK;
}

static void afficher_definition(const Variable *variable)
{
    switch (variable->type) {
    case VAR_INT:
        printf("Variable %s définie avec la valeur %lld (entier)\n",
               variable->name, variable->valeur.entier);
        break;
    case VAR_REAL:
        printf("Variable %s définie avec la valeur %.10g (nombre réel)\n",
               variable->name, variable->valeur.reel);
        break;
    case VAR_STRING:
        printf("Variable %s définie avec la valeur \"%s\" (chaîne de caractères)\n",
               variable->name, variable->valeur.chaine);
        break;
    default:
        break;
    }
}

static void afficher_erreur_definition(StatutSymbole statut, const char *nom)
{
    switch (statut) {
    case SYMBOLE_ERR_TYPE:
        printf("Erreur : changement de type non autorisé pour la variable %s\n", nom);
        break;
    case SYMBOLE_ERR_VALEUR:
        printf("Erreur : valeur invalide pour la variable %s\n", nom);
        break;
    case SYMBOLE_ERR_NOM:
        printf("Erreur : nom de variable invalide.\n");
        break;
    case SYMBOLE_ERR_PLEIN:
        printf("Erreur : table de variables pleine.\n");
        break;
    case SYMBOLE_ERR_SYNTAXE:
        printf("Erreur : syntaxe invalide pour l'affectation.\n");
        break;
    default:
        break;
    }
}

void symboles_traiter_affectation(const char *ligne)
{
    char copie[1024];
    snprintf(copie, sizeof copie, "%s", ligne);

    char *egal = NULL;
    int dans_guillemets = 0;
    for (char *curseur = copie; *curseur != '\0'; curseur++) {
        if (*curseur == '"' && (curseur == copie || curseur[-1] != '\\')) {
            dans_guillemets = !dans_guillemets;
        } else if (*curseur == '=' && !dans_guillemets) {
            egal = curseur;
            break;
        }
    }

    if (egal == NULL) {
        printf("Erreur : syntaxe invalide pour l'affectation.\n");
        return;
    }

    *egal = '\0';
    char *nom = copie;
    char *valeur = egal + 1;

    supprimer_espaces_extremes(nom);
    supprimer_espaces_extremes(valeur);

    Variable *variable = NULL;
    const StatutSymbole statut = symboles_definir(nom, valeur, &variable);

    if (statut == SYMBOLE_OK) {
        afficher_definition(variable);
    } else {
        afficher_erreur_definition(statut, nom);
    }
}

void symboles_afficher(const Variable *variable)
{
    if (variable == NULL) {
        return;
    }

    switch (variable->type) {
    case VAR_INT:
        printf("%lld\n", variable->valeur.entier);
        break;
    case VAR_REAL:
        printf("%.10g\n", variable->valeur.reel);
        break;
    case VAR_STRING:
        printf("\"%s\"\n", variable->valeur.chaine);
        break;
    default:
        break;
    }
}
