CC      ?= cc
CFLAGS  ?= -std=c11 -Wall -Wextra -Wpedantic -O2

.PHONY: all tp1 tp2 interpreteur test clean

all: tp1 tp2 interpreteur

tp1:
	$(MAKE) -C TP1 CFLAGS="$(CFLAGS)"

tp2:
	$(MAKE) -C TP2 CFLAGS="$(CFLAGS)"

interpreteur:
	$(MAKE) -C interpreteur CFLAGS="$(CFLAGS)"

test: all
	$(MAKE) -C tests test
	bash tests/test_tp1.sh
	bash tests/test_tp2.sh
	bash tests/test_interpreteur.sh

clean:
	$(MAKE) -C TP1 clean
	$(MAKE) -C TP2 clean
	$(MAKE) -C interpreteur clean
	$(MAKE) -C tests clean
