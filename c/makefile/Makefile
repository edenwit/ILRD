# Version 1.3 
#Requirements : folder name is target, check "make help" to see correct layout
TARGET = $(notdir ${PWD})

SRC = .
BIN = ../../bin
INC = ../../include
OBJ = ../../obj/$(TARGET)
LIB = ../../lib
ARCHIVE = nir

TEST = ../../test

CC = gcc
#gd flags
CFLAGS = -ansi -pedantic-errors -Wall -Wextra -g -I$(INC)
LDFLAGS = -L$(LIB) -l$(ARCHIVE)

SOURCE = $(wildcard $(SRC)/*.c $(TEST)/$(TARGET)_test.c)
OBJECT = $(patsubst %,$(OBJ)/%, $(notdir $(SOURCE:.c=.o)))


$(BIN)/$(TARGET) : $(OBJECT)
	$(CC) $(CFLAGS) $^ -o $@  $(LDFLAGS)

$(OBJ)/%.o : $(SRC)/%.c 
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ)/%.o : $(TEST)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJECT): | $(OBJ)

$(OBJ):
	mkdir -p $@ 
.PHONY: help run clean tree release dir debug 

dir:
	@mkdir -p $(OBJ)
archive:
	$(AR) r $(LIB)/lib$(ARCHIVE).a $(filter-out %_test.o, $(OBJECT))
tree:
	@tree ../../

release: CFLAGS=-ansi -pedantic-errors -Wall -Wextra -DNDEBUG -o3 -I$(INC)
release: $(BIN)/$(TARGET) 

run:
	./$(BIN)/$(TARGET)
clean:
	rm -f $(OBJECT) $(BIN)/$(TARGET)
debug:
	cgdb $(BIN)/$(TARGET)
vlg:
	valgrind --leak-check=yes --track-origins=yes $(BIN)/$(TARGET)
help:
	@echo "target : $(TARGET)"
	@echo "src: $(SOURCE)"
	@echo "obj: $(OBJECT)"
	@echo "exe: $(BIN)"
	@echo "lib: $(LIB)"
	@echo "test: $(TEST)/$(TARGET)_test"
#By Nir Ben Menachem
