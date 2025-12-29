CC      ?= cc
CFLAGS  ?= -std=c11 -Wall -Wextra -Wpedantic -O2 -Werror
CPPFLAGS ?= -I../interpreteur/src

BUILD   := ../build/tests
TEST_SRC := test_main.c test_lexer.c test_parseur.c test_evaluation.c test_postfixe.c \
            test_symboles.c test_lambda.c
LIB_SRC  := ../interpreteur/src/lexer.c ../interpreteur/src/parseur.c \
            ../interpreteur/src/evaluation.c ../interpreteur/src/postfixe.c \
            ../interpreteur/src/symboles.c ../interpreteur/src/lambda.c

TEST_OBJ := $(patsubst %.c,$(BUILD)/%.o,$(notdir $(TEST_SRC)))
LIB_OBJ  := $(patsubst ../interpreteur/src/%.c,$(BUILD)/%.o,$(LIB_SRC))
OBJ      := $(TEST_OBJ) $(LIB_OBJ)

all: run_tests

$(BUILD):
	mkdir -p $(BUILD)

$(BUILD)/%.o: %.c | $(BUILD)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

$(BUILD)/%.o: ../interpreteur/src/%.c | $(BUILD)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

run_tests: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@ -lm

test: run_tests
	./run_tests

clean:
	rm -rf $(BUILD) run_tests

.PHONY: all test clean
