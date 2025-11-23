#!/usr/bin/env bash
# Golden tests for the standalone TP2 programs.
set -u

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
cd "$ROOT" || exit 1

make -C TP2 >/dev/null || exit 1

fail=0

check_output() {
    local name="$1"
    local expected="$2"
    shift 2
    local output
    output="$("$@" 2>&1)" || true
    if grep -Fq -- "$expected" <<< "$output"; then
        printf 'ok - %s\n' "$name"
    else
        printf 'not ok - %s\n' "$name"
        printf '  expected to find: %s\n' "$expected"
        printf '  actual output:\n%s\n' "$output"
        fail=1
    fi
}

check_stdin() {
    local name="$1"
    local expected="$2"
    local input="$3"
    local program="$4"
    local output
    output="$(printf '%s' "$input" | "$program" 2>&1)" || true
    if grep -Fq -- "$expected" <<< "$output"; then
        printf 'ok - %s\n' "$name"
    else
        printf 'not ok - %s\n' "$name"
        printf '  expected to find: %s\n' "$expected"
        printf '  actual output:\n%s\n' "$output"
        fail=1
    fi
}

check_output "aire" "L'aire du cercle de rayon 5.00 est 78.54" ./TP2/bin/aire
check_output "erreurs (version corrigée)" "100 éléments parcourus sans dépassement." ./TP2/bin/erreurs
check_output "sphere (volume)" "Le volume de la sphère de rayon 5.00 est 523.60" ./TP2/bin/sphere
check_output "sphere (surface)" "La surface de la sphère de rayon 5.00 est 314.16" ./TP2/bin/sphere
check_stdin "chaine (longueur)" 'Longueur de "Bonjour" : 7' $'Bonjour\nMonde\n' ./TP2/bin/chaine
check_stdin "chaine (concaténation)" "Concaténation : BonjourMonde" $'Bonjour\nMonde\n' ./TP2/bin/chaine
check_output "phrases (total)" "Total : 3 occurrence(s)" bash -c 'printf "%s\n%s\n" "TP2/src/montexte.txt" "Bonjour" | ./TP2/bin/phrases'
check_output "couleurs (distinctes)" "Couleurs distinctes : 7" ./TP2/bin/couleurs
check_stdin "chercher (trouvée)" "Phrase trouvée" $'La programmation en C est amusante.\n' ./TP2/bin/chercher
check_stdin "chercher (non trouvée)" "Phrase non trouvée" $'Je préfère le Python.\n' ./TP2/bin/chercher

students=$'Alice\nMartin\n1 rue de Lyon\n18.5\nBob\nDurand\n2 rue de Paris\n12\nCarla\nPetit\n3 avenue Victor Hugo\n15\nDavid\nMoreau\n4 place Bellecour\n9.5\nEmma\nRoux\n5 quai Saint-Antoine\n20\n'
check_stdin "bd_ecole (nom)" "Nom     : Alice" "$students" ./TP2/bin/bd_ecole
check_stdin "bd_ecole (note)" "Note    : 18.50 / 20" "$students" ./TP2/bin/bd_ecole

if [ ! -s TP2/src/programmation_C.md ]; then
    printf 'not ok - programmation_C.md is missing or empty\n'
    fail=1
else
    printf 'ok - programmation_C.md\n'
fi

if [ "$fail" -ne 0 ]; then
    printf '\nTP2: some checks failed\n'
    exit 1
fi

printf '\nTP2: all checks passed\n'
