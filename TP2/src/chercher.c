/*
 * chercher.c — Exercice 2.8
 * Recherche une phrase dans un tableau de dix phrases sans utiliser
 * les fonctions de comparaison ou de recherche de <string.h>.
 */

#include <stdio.h>

#define NB_PHRASES 10
#define TAILLE_PHRASE 128

static int longueur(const char *texte)
{
    int n = 0;
    while (texte[n] != '\0') {
        n++;
    }
    return n;
}

static int phrases_egales(const char *gauche, const char *droite)
{
    int i = 0;
    while (gauche[i] != '\0' && droite[i] != '\0') {
        if (gauche[i] != droite[i]) {
            return 0;
        }
        i++;
    }
    return gauche[i] == droite[i];
}

static void enlever_fin_de_ligne(char *texte)
{
    int n = longueur(texte);
    while (n > 0 && (texte[n - 1] == '\n' || texte[n - 1] == '\r')) {
        texte[--n] = '\0';
    }
}

int main(void)
{
    const char *phrases[NB_PHRASES] = {
        "Bonjour, comment ça va ?",
        "Le temps est magnifique aujourd'hui.",
        "C'est une belle journée.",
        "La programmation en C est amusante.",
        "Les tableaux en C sont puissants.",
        "Les pointeurs en C peuvent être déroutants.",
        "Il fait beau dehors.",
        "La recherche dans un tableau est intéressante.",
        "Les structures de données sont importantes.",
        "Programmer en C, c'est génial."
    };

    char recherche[TAILLE_PHRASE];

    printf("Phrase à rechercher : ");
    if (fgets(recherche, sizeof recherche, stdin) == NULL) {
        return 1;
    }
    enlever_fin_de_ligne(recherche);

    int trouvee = 0;
    for (int i = 0; i < NB_PHRASES; i++) {
        if (phrases_egales(recherche, phrases[i])) {
            trouvee = 1;
            break;
        }
    }

    if (trouvee) {
        printf("Phrase trouvée\n");
    } else {
        printf("Phrase non trouvée\n");
    }

    return 0;
}
