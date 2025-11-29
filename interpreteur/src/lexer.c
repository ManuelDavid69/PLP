#include "lexer.h"

#include <ctype.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

static int est_debut_identifiant(unsigned char c)
{
    return isalpha(c) || c == '_' || c >= 0x80;
}

static int est_caractere_identifiant(unsigned char c)
{
    return isalnum(c) || c == '_' || c >= 0x80;
}

void lexer_init(Lexer *lexer, const char *input)
{
    lexer->input = input;
    lexer->pos = 0;
}

static Token token_operateur(TokenType type, const char *texte)
{
    Token token;
    memset(&token, 0, sizeof token);
    token.type = type;
    strcpy(token.text, texte);
    return token;
}

static Token token_erreur(void)
{
    Token token;
    memset(&token, 0, sizeof token);
    token.type = TOKEN_ERROR;
    return token;
}

Token lexer_next_token(Lexer *lexer)
{
    Token token;
    memset(&token, 0, sizeof token);
    token.type = TOKEN_END;

    const char *entree = lexer->input;

    while (isspace((unsigned char)entree[lexer->pos])) {
        lexer->pos++;
    }

    const char c = entree[lexer->pos];
    if (c == '\0') {
        return token;
    }

    /* Nombre entier ou réel : 12, 12.5, .5, 1e-3. */
    if (isdigit((unsigned char)c) ||
        (c == '.' && isdigit((unsigned char)entree[lexer->pos + 1]))) {
        errno = 0;
        char *fin = NULL;
        const double valeur = strtod(entree + lexer->pos, &fin);
        const size_t longueur = (size_t)(fin - (entree + lexer->pos));

        if (longueur == 0 || longueur >= sizeof token.text || errno == ERANGE) {
            token = token_erreur();
            lexer->pos += (longueur > 0) ? longueur : 1;
            return token;
        }

        /* Refuse 1.2.3 ou 12abc : le nombre doit être suivi d'un séparateur. */
        if (*fin == '.' || est_debut_identifiant((unsigned char)*fin)) {
            token = token_erreur();
            lexer->pos += longueur;
            return token;
        }

        memcpy(token.text, entree + lexer->pos, longueur);
        token.text[longueur] = '\0';
        token.type = TOKEN_NUMBER;
        token.number = valeur;
        lexer->pos += longueur;
        return token;
    }

    /* Chaîne de caractères entre guillemets, avec échappements simples. */
    if (c == '"') {
        size_t i = lexer->pos + 1;
        size_t j = 0;

        while (entree[i] != '\0' && entree[i] != '"') {
            char caractere = entree[i];

            if (caractere == '\\' && entree[i + 1] != '\0') {
                i++;
                switch (entree[i]) {
                case 'n':
                    caractere = '\n';
                    break;
                case 't':
                    caractere = '\t';
                    break;
                default:
                    caractere = entree[i];
                    break;
                }
            }

            if (j + 1 >= sizeof token.text) {
                token = token_erreur();
                lexer->pos = i;
                return token;
            }

            token.text[j++] = caractere;
            i++;
        }

        if (entree[i] != '"') {
            token = token_erreur();
            lexer->pos = i;
            return token;
        }

        token.text[j] = '\0';
        token.type = TOKEN_STRING;
        lexer->pos = i + 1;
        return token;
    }

    /* Identifiant, y compris les noms UTF-8 (octets >= 0x80). */
    if (est_debut_identifiant((unsigned char)c)) {
        const size_t debut = lexer->pos;
        lexer->pos++;

        while (est_caractere_identifiant((unsigned char)entree[lexer->pos])) {
            lexer->pos++;
        }

        const size_t longueur = lexer->pos - debut;
        if (longueur >= sizeof token.text) {
            return token_erreur();
        }

        memcpy(token.text, entree + debut, longueur);
        token.text[longueur] = '\0';
        token.type = TOKEN_IDENTIFIER;
        return token;
    }

    lexer->pos++;

    switch (c) {
    case '+':
        return token_operateur(TOKEN_PLUS, "+");
    case '-':
        return token_operateur(TOKEN_MINUS, "-");
    case '*':
        return token_operateur(TOKEN_STAR, "*");
    case '/':
        return token_operateur(TOKEN_SLASH, "/");
    case '(':
        return token_operateur(TOKEN_LPAREN, "(");
    case ')':
        return token_operateur(TOKEN_RPAREN, ")");
    case '.':
        return token_operateur(TOKEN_DOT, ".");
    case '=':
        return token_operateur(TOKEN_EQUAL, "=");
    default:
        return token_erreur();
    }
}

const char *token_type_name(TokenType type)
{
    switch (type) {
    case TOKEN_NUMBER:
        return "nombre";
    case TOKEN_IDENTIFIER:
        return "identifiant";
    case TOKEN_STRING:
        return "chaîne";
    case TOKEN_PLUS:
        return "plus";
    case TOKEN_MINUS:
        return "moins";
    case TOKEN_STAR:
        return "étoile";
    case TOKEN_SLASH:
        return "slash";
    case TOKEN_LPAREN:
        return "parenthèse ouvrante";
    case TOKEN_RPAREN:
        return "parenthèse fermante";
    case TOKEN_DOT:
        return "point";
    case TOKEN_EQUAL:
        return "égal";
    case TOKEN_END:
        return "fin";
    case TOKEN_ERROR:
        return "erreur";
    default:
        return "inconnu";
    }
}
