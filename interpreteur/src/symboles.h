#ifndef SYMBOLES_H
#define SYMBOLES_H

#include <stddef.h>

typedef enum {
    VAR_INT,
    VAR_REAL,
    VAR_STRING
} VarType;

typedef struct {
    char name[128];
    VarType type;
    union {
        long long entier;
        double reel;
        char chaine[256];
    } valeur;
} Variable;

typedef enum {
    SYMBOLE_OK = 0,
    SYMBOLE_ERR_NOM,
    SYMBOLE_ERR_SYNTAXE,
    SYMBOLE_ERR_VALEUR,
    SYMBOLE_ERR_TYPE,
    SYMBOLE_ERR_PLEIN
} StatutSymbole;

void symboles_init(void);
Variable *symboles_chercher(const char *nom);
StatutSymbole symboles_definir(const char *nom, const char *valeur_brute, Variable **resultat);
int symboles_est_affectation(const char *ligne);
int symboles_est_nom(const char *ligne);
void symboles_afficher(const Variable *variable);
void symboles_traiter_affectation(const char *ligne);
const char *symboles_nom_type(VarType type);

#endif
