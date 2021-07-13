NAME = $(notdir ${PWD})
LIB = ../../lib
TEST = ../test
OBJ = ../../obj
INC = ../../include
SRC = .
BIN = ../bin
SRCS := $(NAME)/$(wildcard $(SRC)/*.c)
export EXES_SRC := $(TEST)/$(NAME:.c=_test.c)
export EXES := $(BIN)/$(NAME:=_test)
all:
	$(MAKE) all -C../ -e

debug:
	$(MAKE) debug -C../ -e

release:
	$(MAKE) release -C../ -e

test:
	$(MAKE) test -C../ -e

.PHONY: clean all release debug test run gdb

gdb:
	@cd ../ && cgdb $(BIN)/$(NAME)_test
run:
	@cd ../ && $(BIN)/$(NAME)_test
help:
	$(MAKE) help -C../ -e
clean:
	$(MAKE) clean -C../ -e
