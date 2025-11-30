#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "evaluation.h"
#include "lexer.h"
#include "parseur.h"

/**
 * Interpréteur de commandes — TP3.
 *
 * Ce premier niveau gère les commandes de base (echo, help/aide, version,
 * date, quit/quitter), puis les expressions arithmétiques simples « A op B ».
 */

static int programme_en_cours = 1;

static int egales_sans_casse(const char *gauche, const char *droite)
{
    while (*gauche != '\0' && *droite != '\0') {
        if (tolower((unsigned char)*gauche) != tolower((unsigned char)*droite)) {
            return 0;
        }
        gauche++;
        droite++;
    }
    return *gauche == '\0' && *droite == '\0';
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

static void traiter_echo(const char *arguments)
{
    if (arguments == NULL) {
        arguments = "";
    }
    printf("Echo: %s\n", arguments);
}

static void afficher_version(const char *arguments)
{
    (void)arguments;
    printf("Interpréteur PLP - version 1.0\n");
}

static void afficher_aide(const char *arguments)
{
    (void)arguments;
    printf("Commandes disponibles :\n");
    printf("  echo <texte>      affiche le texte fourni\n");
    printf("  date              affiche la date et l'heure courantes\n");
    printf("  version           affiche la version de l'interpréteur\n");
    printf("  help / aide       affiche cette aide\n");
    printf("  quit / quitter    quitte l'interpréteur\n");
    printf("  <A op B>          évalue une expression simple, par exemple 2 + 3\n");
}

static void traiter_date(const char *arguments)
{
    (void)arguments;

    time_t maintenant = time(NULL);
    struct tm *local = localtime(&maintenant);

    if (local == NULL) {
        printf("Erreur : impossible de lire la date courante.\n");
        return;
    }

    printf("Date actuelle : %02d/%02d/%04d %02d:%02d:%02d\n",
           local->tm_mday,
           local->tm_mon + 1,
           local->tm_year + 1900,
           local->tm_hour,
           local->tm_min,
           local->tm_sec);
}

static void traiter_quit(const char *arguments)
{
    (void)arguments;
    printf("Arrêt...\n");
    programme_en_cours = 0;
}

struct Commande {
    const char *nom;
    void (*fonction)(const char *arguments);
};

static const struct Commande COMMANDES[] = {
    {"echo", traiter_echo},
    {"help", afficher_aide},
    {"aide", afficher_aide},
    {"version", afficher_version},
    {"date", traiter_date},
    {"quit", traiter_quit},
    {"quitter", traiter_quit}
};

static const size_t NB_COMMANDES = sizeof(COMMANDES) / sizeof(COMMANDES[0]);

static int ressemble_a_expression(const char *texte)
{
    int contient_un_chiffre = 0;

    for (const char *curseur = texte; *curseur != '\0'; curseur++) {
        if (isspace((unsigned char)*curseur)) {
            continue;
        }
        if (isdigit((unsigned char)*curseur)) {
            contient_un_chiffre = 1;
        } else if (strchr("+-*/().", *curseur) == NULL) {
            return 0;
        }
    }

    return contient_un_chiffre;
}

static void afficher_nombre(double valeur)
{
    if (valeur >= -9007199254740992.0 && valeur <= 9007199254740992.0 &&
        valeur == (double)(long long)valeur) {
        printf("%lld\n", (long long)valeur);
    } else {
        printf("%.10g\n", valeur);
    }
}

static void interpreter_ligne(const char *ligne)
{
    char copie[1024];
    snprintf(copie, sizeof copie, "%s", ligne);
    supprimer_espaces_extremes(copie);

    if (copie[0] == '\0') {
        return;
    }

    char commande[128];
    size_t i = 0;
    const char *curseur = copie;

    while (*curseur != '\0' && !isspace((unsigned char)*curseur) && i + 1 < sizeof commande) {
        commande[i++] = *curseur++;
    }
    commande[i] = '\0';

    while (*curseur != '\0' && isspace((unsigned char)*curseur)) {
        curseur++;
    }

    for (size_t c = 0; c < NB_COMMANDES; c++) {
        if (egales_sans_casse(commande, COMMANDES[c].nom)) {
            COMMANDES[c].fonction(curseur);
            return;
        }
    }

    if (ressemble_a_expression(copie)) {
        Lexer lexer;
        lexer_init(&lexer, copie);

        Expression expression;
        if (parse_expression(&lexer, &expression)) {
            double resultat;
            if (evaluer_expression(&expression, &resultat)) {
                afficher_nombre(resultat);
            }
        }
        return;
    }

    printf("Commande non reconnue. Tapez 'help' ou 'aide' pour la liste des commandes.\n");
}

int main(void)
{
    printf("Interpréteur PLP 1.0 — tapez 'help' ou 'aide'.\n");

    while (programme_en_cours) {
        printf("> ");
        fflush(stdout);

        char ligne[1024];
        if (fgets(ligne, sizeof ligne, stdin) == NULL) {
            printf("\n");
            break;
        }

        ligne[strcspn(ligne, "\r\n")] = '\0';
        interpreter_ligne(ligne);
        printf("\n");
    }

    return 0;
}
