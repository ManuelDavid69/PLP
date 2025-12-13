#include "postfixe.h"

#include "lexer.h"

#include <stdio.h>
#include <string.h>

#define TAILLE_PILE 256

typedef struct {
    char operations[TAILLE_PILE];
    int sommet;
} PileOperateurs;

static void pile_init(PileOperateurs *pile)
{
    pile->sommet = -1;
}

static int pile_vide(const PileOperateurs *pile)
{
    return pile->sommet == -1;
}

static int pile_pousser(PileOperateurs *pile, char operation)
{
    if (pile->sommet + 1 >= TAILLE_PILE) {
        return 0;
    }
    pile->operations[++pile->sommet] = operation;
    return 1;
}

static char pile_depiler(PileOperateurs *pile)
{
    return pile->operations[pile->sommet--];
}

static char pile_sommet(const PileOperateurs *pile)
{
    return pile->operations[pile->sommet];
}

static int priorite(char operation)
{
    switch (operation) {
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
        return 2;
    case 'u': /* moins unaire */
        return 3;
    default:
        return 0;
    }
}

static int ajouter_texte(char *sortie, size_t taille, size_t *position, const char *texte)
{
    const size_t longueur = strlen(texte);

    if (*position + longueur + 2 > taille) {
        return 0;
    }

    memcpy(sortie + *position, texte, longueur);
    *position += longueur;
    sortie[*position] = ' ';
    (*position)++;
    sortie[*position] = '\0';
    return 1;
}

int infix_to_postfix(const char *infixe, char *postfixe, size_t taille)
{
    Lexer lexer;
    PileOperateurs pile;
    size_t position = 0;
    int attend_operande = 1;

    if (infixe == NULL || postfixe == NULL || taille == 0) {
        return 0;
    }

    postfixe[0] = '\0';
    lexer_init(&lexer, infixe);
    pile_init(&pile);

    for (;;) {
        Token jeton = lexer_next_token(&lexer);

        if (jeton.type == TOKEN_END) {
            break;
        }

        if (jeton.type == TOKEN_NUMBER) {
            if (!attend_operande) {
                fprintf(stderr, "Erreur : deux opérandes se suivent sans opérateur.\n");
                return 0;
            }
            if (!ajouter_texte(postfixe, taille, &position, jeton.text)) {
                fprintf(stderr, "Erreur : expression trop longue.\n");
                return 0;
            }
            attend_operande = 0;
            continue;
        }

        if (jeton.type == TOKEN_LPAREN) {
            if (!attend_operande) {
                fprintf(stderr, "Erreur : un opérateur est attendu avant '('.\n");
                return 0;
            }
            if (!pile_pousser(&pile, '(')) {
                fprintf(stderr, "Erreur : pile d'opérateurs saturée.\n");
                return 0;
            }
            attend_operande = 1;
            continue;
        }

        if (jeton.type == TOKEN_RPAREN) {
            if (attend_operande) {
                fprintf(stderr, "Erreur : parenthèse fermante mal placée.\n");
                return 0;
            }

            while (!pile_vide(&pile) && pile_sommet(&pile) != '(') {
                const char sommet = pile_depiler(&pile);
                char texte[2] = {sommet, '\0'};
                if (!ajouter_texte(postfixe, taille, &position, texte)) {
                    fprintf(stderr, "Erreur : expression trop longue.\n");
                    return 0;
                }
            }

            if (pile_vide(&pile)) {
                fprintf(stderr, "Erreur : parenthèse fermante sans parenthèse ouvrante.\n");
                return 0;
            }
            pile_depiler(&pile); /* retire '(' */
            attend_operande = 0;
            continue;
        }

        if (jeton.type == TOKEN_PLUS || jeton.type == TOKEN_MINUS ||
            jeton.type == TOKEN_STAR || jeton.type == TOKEN_SLASH) {

            /* Moins unaire : -3, 2 * -3, (-3 + 4). */
            if (attend_operande && jeton.type == TOKEN_MINUS) {
                if (!pile_pousser(&pile, 'u')) {
                    fprintf(stderr, "Erreur : pile d'opérateurs saturée.\n");
                    return 0;
                }
                continue;
            }

            /* Plus unaire : +3 est équivalent à 3. */
            if (attend_operande && jeton.type == TOKEN_PLUS) {
                continue;
            }

            if (attend_operande) {
                fprintf(stderr, "Erreur : opérateur mal placé.\n");
                return 0;
            }

            const char operation = jeton.text[0];
            while (!pile_vide(&pile) &&
                   pile_sommet(&pile) != '(' &&
                   priorite(pile_sommet(&pile)) >= priorite(operation)) {
                const char sommet = pile_depiler(&pile);
                char texte[2] = {sommet, '\0'};
                if (!ajouter_texte(postfixe, taille, &position, texte)) {
                    fprintf(stderr, "Erreur : expression trop longue.\n");
                    return 0;
                }
            }

            if (!pile_pousser(&pile, operation)) {
                fprintf(stderr, "Erreur : pile d'opérateurs saturée.\n");
                return 0;
            }
            attend_operande = 1;
            continue;
        }

        fprintf(stderr, "Erreur : caractère inattendu dans l'expression.\n");
        return 0;
    }

    if (attend_operande) {
        fprintf(stderr, "Erreur : expression incomplète.\n");
        return 0;
    }

    while (!pile_vide(&pile)) {
        const char sommet = pile_depiler(&pile);
        if (sommet == '(') {
            fprintf(stderr, "Erreur : parenthèse ouvrante non fermée.\n");
            return 0;
        }
        char texte[2] = {sommet, '\0'};
        if (!ajouter_texte(postfixe, taille, &position, texte)) {
            fprintf(stderr, "Erreur : expression trop longue.\n");
            return 0;
        }
    }

    if (position > 0 && postfixe[position - 1] == ' ') {
        postfixe[position - 1] = '\0';
    }

    return 1;
}
