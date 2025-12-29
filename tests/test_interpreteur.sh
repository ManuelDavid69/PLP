#!/usr/bin/env bash
# End-to-end tests for the REPL (TP3, TP4 and TP5).
set -u

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
cd "$ROOT" || exit 1

make -C interpreteur >/dev/null || exit 1

output="$(
    printf '%s\n' \
        'echo Bonjour à tous' \
        'help' \
        'version' \
        'date' \
        'bonjour le monde' \
        '2 + 3' \
        '1.2 * 4.0' \
        '3 + 4 * 5' \
        '(3 + 4) * 5' \
        '10 / 0' \
        'x = 4' \
        'x' \
        'x = 12.3' \
        'z = "Bonjour"' \
        'z' \
        'π = 3.14' \
        'π' \
        'y = 4' \
        '(lambda x.x + 2 * x) 3' \
        '(lambda x.(x + 2) * x) y' \
        '(lambda x.x + 1) w' \
        'quitter' |
        ./interpreteur/interpreteur 2>&1
)"

fail=0

check() {
    local name="$1"
    local expected="$2"
    if grep -Fq -- "$expected" <<< "$output"; then
        printf 'ok - %s\n' "$name"
    else
        printf 'not ok - %s\n' "$name"
        printf '  expected to find: %s\n' "$expected"
        fail=1
    fi
}

check "echo" "Echo: Bonjour à tous"
check "help" "Commandes disponibles"
check "version" "version 1.0"
check "date" "Date actuelle"
check "commande inconnue" "Commande non reconnue."
check "addition" "> 5"
check "réel" "> 4.8"
check "priorités" "> 23"
check "parenthèses" "> 35"
check "division par zéro" "division par zéro"
check "affectation entière" "Variable x définie avec la valeur 4 (entier)"
check "lecture variable" "> 4"
check "changement de type" "changement de type non autorisé"
check "affectation chaîne" 'Variable z définie avec la valeur "Bonjour" (chaîne de caractères)'
check "lecture chaîne" '> "Bonjour"'
check "affectation réelle" "Variable π définie avec la valeur 3.14 (nombre réel)"
check "lecture réelle" "> 3.14"
check "lambda numérique" "> 9"
check "lambda variable" "> 24"
check "lambda variable inconnue" "la variable w n'est pas définie"
check "quitter" "Arrêt..."

if [ "$fail" -ne 0 ]; then
    printf '\nInterpréteur : certains tests ont échoué\n'
    printf '%s\n' "$output"
    exit 1
fi

printf '\nInterpréteur : tous les tests sont passés\n'
