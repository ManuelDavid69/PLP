CC      ?= cc
CFLAGS  ?= -std=c11 -Wall -Wextra -Wpedantic -O2
LDLIBS  ?= -lm

SINGLE := $(filter-out src/main.c src/surface.c src/volume.c,$(wildcard src/*.c))
BIN    := $(patsubst src/%.c,bin/%,$(SINGLE)) bin/sphere

all: $(BIN)

bin:
	mkdir -p bin

bin/%: src/%.c | bin
	$(CC) $(CFLAGS) $< -o $@ $(LDLIBS)

bin/sphere: src/main.c src/surface.c src/volume.c | bin
	$(CC) $(CFLAGS) $^ -o $@ $(LDLIBS)

test: all
	@echo "Lancez tests/test_tp2.sh pour les tests de sortie."

clean:
	rm -rf bin

.PHONY: all test clean
