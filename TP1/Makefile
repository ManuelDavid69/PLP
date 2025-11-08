CC      ?= cc
CFLAGS  ?= -std=c11 -Wall -Wextra -Wpedantic -O2
LDLIBS  ?= -lm

SRC := $(wildcard src/*.c)
BIN := $(patsubst src/%.c,bin/%,$(SRC))

all: $(BIN)

bin:
	mkdir -p bin

bin/%: src/%.c | bin
	$(CC) $(CFLAGS) $< -o $@ $(LDLIBS)

test: all
	./bin/bonjour

clean:
	rm -rf bin

.PHONY: all test clean
