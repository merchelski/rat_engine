CC=gcc
CFLAGS= -g -std=c99 -Wall -Wextra -Werror -pedantic
GCCOPTIONS= -mbmi2
SRC=src
OBJ=obj
SRCS=$(wildcard $(SRC)/*.c)
OBJS=$(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SRCS))

BINDIR=bin
BIN=$(BINDIR)/main

all:$(BIN)

$(BIN): $(OBJS)
	$(CC) $(CFLAGS) $(GCCOPTIONS) $(OBJS) -o $@

$(OBJ)/%.o: $(SRC)/%.c
	$(CC) $(CFLAGS) $(GCCOPTIONS) -c $< -o $@

clean:
	$(RM) -r $(BIN) $(OBJ)/*

run:
	./$(BIN)
