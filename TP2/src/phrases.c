/*
 * phrases.c — Exercice 2.6
 * Recherche une phrase dans un fichier et compte ses occurrences ligne par ligne.
 */

#include <stdio.h>
#include <string.h>

#define TAILLE_LIGNE 1024
#define TAILLE_NOM 256
#define TAILLE_PHRASE 256

static void enlever_fin_de_ligne(char *texte)
{
    size_t longueur = strlen(texte);
    while (longueur > 0 && (texte[longueur - 1] == '\n' || texte[longueur - 1] == '\r')) {
        texte[--longueur] = '\0';
    }
}

static int compter_occurrences(const char *ligne, const char *phrase)
{
    const size_t longueur = strlen(phrase);
    if (longueur == 0) {
        return 0;
    }

    int occurrences = 0;
    const char *position = ligne;

    while ((position = strstr(position, phrase)) != NULL) {
        occurrences++;
        position += longueur;
    }

    return occurrences;
}

int main(void)
{
    char nom_fichier[TAILLE_NOM];
    char phrase[TAILLE_PHRASE];
    char ligne[TAILLE_LIGNE];

    printf("Nom du fichier : ");
    if (fgets(nom_fichier, sizeof nom_fichier, stdin) == NULL) {
        return 1;
    }
    enlever_fin_de_ligne(nom_fichier);

    printf("Phrase à rechercher : ");
    if (fgets(phrase, sizeof phrase, stdin) == NULL) {
        return 1;
    }
    enlever_fin_de_ligne(phrase);

    if (nom_fichier[0] == '\0' || phrase[0] == '\0') {
        fprintf(stderr, "Erreur : le nom du fichier et la phrase doivent être renseignés.\n");
        return 1;
    }

    FILE *fichier = fopen(nom_fichier, "r");
    if (fichier == NULL) {
        perror("fopen");
        return 1;
    }

    printf("\nRecherche de \"%s\" dans %s\n", phrase, nom_fichier);
    printf("------------------------------------------------------------\n");

    int numero_ligne = 0;
    int total = 0;

    while (fgets(ligne, sizeof ligne, fichier) != NULL) {
        numero_ligne++;
        int occurrences = compter_occurrences(ligne, phrase);
        if (occurrences > 0) {
            char affichage[TAILLE_LIGNE];
            snprintf(affichage, sizeof affichage, "%s", ligne);
            enlever_fin_de_ligne(affichage);
            printf("Ligne %4d : %3d occurrence(s) | %s\n", numero_ligne, occurrences, affichage);
        }
        total += occurrences;
    }

    fclose(fichier);

    printf("------------------------------------------------------------\n");
    printf("Total : %d occurrence(s)\n", total);

    return 0;
}
