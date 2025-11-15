/*
 * bd_ecole.c — Exercice 2.5
 * Gestion d'une petite base de données de cinq étudiant·e·s.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NB_ETUDIANTS 5

struct Etudiant {
    char nom[30];
    char prenom[30];
    char adresse[100];
    float note;
};

static void lire_ligne(char *buffer, size_t taille)
{
    if (fgets(buffer, (int)taille, stdin) == NULL) {
        buffer[0] = '\0';
        return;
    }

    size_t longueur = strlen(buffer);
    while (longueur > 0 && (buffer[longueur - 1] == '\n' || buffer[longueur - 1] == '\r')) {
        buffer[--longueur] = '\0';
    }
}

static float lire_note(void)
{
    char buffer[32];
    lire_ligne(buffer, sizeof buffer);

    char *fin = NULL;
    float note = strtof(buffer, &fin);

    if (fin == buffer) {
        fprintf(stderr, "Erreur : note invalide, 0 utilisée.\n");
        return 0.0f;
    }

    while (*fin == ' ' || *fin == '\t') {
        fin++;
    }
    if (*fin != '\0') {
        fprintf(stderr, "Erreur : caractères en trop après la note, 0 utilisée.\n");
        return 0.0f;
    }

    if (note < 0.0f || note > 20.0f) {
        fprintf(stderr, "Erreur : la note doit être comprise entre 0 et 20.\n");
        return 0.0f;
    }

    return note;
}

int main(void)
{
    struct Etudiant etudiants[NB_ETUDIANTS];
    char nom[30];
    char prenom[30];
    char adresse[100];

    for (int i = 0; i < NB_ETUDIANTS; i++) {
        printf("\n--- Étudiant %d ---\n", i + 1);

        printf("Nom : ");
        lire_ligne(nom, sizeof nom);
        strcpy(etudiants[i].nom, nom);

        printf("Prénom : ");
        lire_ligne(prenom, sizeof prenom);
        strcpy(etudiants[i].prenom, prenom);

        printf("Adresse : ");
        lire_ligne(adresse, sizeof adresse);
        strcpy(etudiants[i].adresse, adresse);

        printf("Note (sur 20) : ");
        etudiants[i].note = lire_note();
    }

    printf("\n===== Liste des étudiant·e·s =====\n");
    for (int i = 0; i < NB_ETUDIANTS; i++) {
        printf("\nÉtudiant %d\n", i + 1);
        printf("  Nom     : %s\n", etudiants[i].nom);
        printf("  Prénom  : %s\n", etudiants[i].prenom);
        printf("  Adresse : %s\n", etudiants[i].adresse);
        printf("  Note    : %.2f / 20\n", (double)etudiants[i].note);
    }

    return 0;
}
