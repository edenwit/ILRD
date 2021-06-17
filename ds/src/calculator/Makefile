TARGET = $(notdir $(shell pwd))
SHAREDLIB = lib$(notdir $(shell pwd)).so
TEST_TARGET = $(TARGET)_test
STACKSHAREDLIB = libstack.so

SRC = .
INC = ../../include
BIN = ../../bin
LIB = /home/edenwit/git/eden-wittenberg/ds/lib
TEST = ../../test
STACK = ../stack


OBJ = ../../obj
CC = gcc
CFLAGS =  -ansi -pedantic-errors -Wall -Wextra -g -I$(INC) 

OBJECTS = $(OBJ)/$(TARGET)/$(TARGET).o 
TEST_OBJECTS = $(OBJ)/$(TARGET)/$(TEST_TARGET).o 
STACK_OBJECT = $(OBJ)/stack/stack.o

#--------------source & test sourec files-------------#
TEST_SOURCE = $(TEST)/$(TEST_TARGET).c
SOURCE = $(SRC)/$(TARGET).c 
STACK_SRC = $(SRC)/$(STACK)/stack.c
#----------------shared object flags------------------#
SOFLAG_FIRST = -c -fpic 
SOFLAG_SECOND = -shared -o
LDFLAGS = -L$(LIB) -Wl,-rpath=$(LIB) -lds
#----------------------------------------------------#

$(STACK_OBJECT): $(STACK)/stack.c $(SOURCE) $(INC)/stack.h 
	$(CC) $(CFLAGS) $(SOFLAG_FIRST) $< -o $@

$(OBJECTS): $(SOURCE) $(INC)/$(TARGET).h
	$(CC) $(CFLAGS) $(SOFLAG_FIRST) $< -o $@

$(LIB)/$(SHAREDLIB): $(OBJECTS) $(SOURCE) 
	$(CC) $(CFLAGS) $(SOFLAG_SECOND) $^ -o $@

$(BIN)/$(TARGET): $(TEST_SOURCE) $(LIB)/libds.so
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@ 
	
$(TEST_OBJECTS).o: $(TEST_SOURCE) $(INC)/$(TARGET).h
		$(CC) $(CFLAGS) $< -c -o $(OBJ)/$(TARGET)/$@

.PHONY : build test so clean

build:
	@mkdir -p $(OBJ)/$(TARGET)  
	@mkdir -p $(OBJ)/$(stack)  
	@make $(BIN)/$(TARGET)
	@make $(BIN)/$(stack)

test:
	@./$(BIN)/$(TARGET)
	
so:
	@mkdir -p $(OBJ)/$(TARGET)  
	@make $(LIB)/$(SHAREDLIB)
	@mkdir -p $(OBJ)/$(stack)  
	@make $(LIB)/$(STACKSHAREDLIB)	

arc:
	ar -vr $(LIB)/libD_S.a $(OBJECTS)

clean :
	rm -f -r $(OBJECTS) $(BIN)/$(TARGET) $(LIB)/$(SHAREDLIB)


