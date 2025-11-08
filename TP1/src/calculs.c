/*
 * calculs.c — Exercice 1.8
 * Petite calculatrice entière utilisant un switch et des opérateurs bit à bit.
 */

#include <stdio.h>

int main(void)
{
    int num1;
    int num2 = 0;
    char op;

    printf("Premier entier : ");
    if (scanf("%d", &num1) != 1) {
        fprintf(stderr, "Erreur : le premier opérande doit être un entier.\n");
        return 1;
    }

    printf("Opérateur (+, -, *, /, %%, &, |, ~) : ");
    if (scanf(" %c", &op) != 1) {
        fprintf(stderr, "Erreur : opérateur manquant.\n");
        return 1;
    }

    if (op != '~' && op != '+' && op != '-' && op != '*' && op != '/' &&
        op != '%' && op != '&' && op != '|') {
        fprintf(stderr, "Erreur : opérateur inconnu '%c'.\n", op);
        return 1;
    }

    if (op != '~') {
        printf("Second entier : ");
        if (scanf("%d", &num2) != 1) {
            fprintf(stderr, "Erreur : le second opérande doit être un entier.\n");
            return 1;
        }
    }

    switch (op) {
    case '+':
        printf("%d + %d = %d\n", num1, num2, num1 + num2);
        break;
    case '-':
        printf("%d - %d = %d\n", num1, num2, num1 - num2);
        break;
    case '*':
        printf("%d * %d = %d\n", num1, num2, num1 * num2);
        break;
    case '/':
        if (num2 == 0) {
            fprintf(stderr, "Erreur : division par zéro interdite.\n");
            return 1;
        }
        printf("%d / %d = %d\n", num1, num2, num1 / num2);
        break;
    case '%':
        if (num2 == 0) {
            fprintf(stderr, "Erreur : modulo par zéro interdit.\n");
            return 1;
        }
        printf("%d %% %d = %d\n", num1, num2, num1 % num2);
        break;
    case '&':
        printf("%d & %d = %d\n", num1, num2, num1 & num2);
        break;
    case '|':
        printf("%d | %d = %d\n", num1, num2, num1 | num2);
        break;
    case '~':
        printf("~%d = %d\n", num1, ~num1);
        break;
    default:
        fprintf(stderr, "Erreur : opérateur inconnu '%c'.\n", op);
        return 1;
    }

    return 0;
}
