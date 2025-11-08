#!/usr/bin/env bash
# Golden tests for the standalone TP1 programs.
set -u

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
cd "$ROOT" || exit 1

make -C TP1 >/dev/null || exit 1

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

check_output "bonjour" "Bonjour le Monde!" ./TP1/bin/bonjour
check_stdin "cercle (aire)" "Aire = 12.57" $'2\n' ./TP1/bin/cercle
check_stdin "cercle (périmètre)" "Périmètre = 12.57" $'2\n' ./TP1/bin/cercle
check_output "sizeof_types" "char                : 1 octet(s)" ./TP1/bin/sizeof_types
check_output "sizeof_types (int)" "int                 : 4 octet(s)" ./TP1/bin/sizeof_types
check_output "variables" "unsigned int        : 4294967295" ./TP1/bin/variables
check_output "operateurs (arithmétique)" "16 + 3 = 19" ./TP1/bin/operateurs
check_output "operateurs (comparaison)" "a >  b : 1" ./TP1/bin/operateurs
check_stdin "boucles (for)" "* # # *" $'5\n' ./TP1/bin/boucles
check_stdin "boucles (while)" "* * * * *" $'5\n' ./TP1/bin/boucles
check_output "controle (4 sans 6)" "4 : divisible par 4 mais pas par 6" ./TP1/bin/controle
check_output "controle (pair et 8)" "24 : pair et divisible par 8" ./TP1/bin/controle
check_output "controle (5 ou 7)" "5 : divisible par 5 ou 7 mais pas par 10" ./TP1/bin/controle
check_stdin "calculs (+)" "16 + 3 = 19" $'16\n+\n3\n' ./TP1/bin/calculs
check_stdin "calculs (~)" "~16 = -17" $'16\n~\n' ./TP1/bin/calculs
check_stdin "calculs (division par zéro)" "division par zéro" $'16\n/\n0\n' ./TP1/bin/calculs
check_output "binaire (0)" "0 en binaire : 0" ./TP1/bin/binaire 0
check_output "binaire (4096)" "4096 en binaire : 1 0000 0000 0000" ./TP1/bin/binaire 4096
check_output "binaire (65535)" "65535 en binaire : 1111 1111 1111 1111" ./TP1/bin/binaire 65535

if [ "$fail" -ne 0 ]; then
    printf '\nTP1: some checks failed\n'
    exit 1
fi

printf '\nTP1: all checks passed\n'
