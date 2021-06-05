
TARGET = $(notdir $(shell pwd))
SHAREDLIB = libds.so
TEST_TARGET = $(TARGET)_test

SRC = .
INC = ../include
BIN = ../bin
LIB = /home/edenwit/git/ds/lib
TEST = ../test

OBJ = ../obj
CC = gcc
CFLAGS =  -ansi -pedantic-errors -Wall -Wextra -g -I$(INC) 

OBJECTS = $(OBJ)/$(TARGET)/$(TARGET).o 
TEST_OBJECTS = $(OBJ)/$(TARGET)/$(TEST_TARGET).o 

#--------------source & test sourec files-------------#
TEST_SOURCE = $(TEST)/$(TEST_TARGET).c
SOURCE = $(SRC)/$(TARGET).c 

#----------------shared object flags------------------#
SOFLAG_FIRST = -c -fPIC 
SOFLAG_SECOND = -shared -o
LDFLAGS = -L$(LIB) -Wl,-rpath=$(LIB) -lds
#----------------------------------------------------#




TOPTARGETS := all
MAKECLEAN = $(shell make clean)

SUBDIRS_LIB := $(wildcard ../lib/$(SHAREDLIB))
SUBDIRS := $(wildcard */.)
SUBOBJ := $(wildcard ../obj/.)


$(TOPTARGETS): $(SUBDIRS) 
$(SUBDIRS):
	@mkdir -p $(OBJ)/$@
$(SUBDIRS):
	$(MAKE) -C $@ $(MAKECMDGOALS)


.PHONY: $(TOPTARGETS) $(SUBDIRS)

libds:
	$(CC) $(CFLAGS) $(SOFLAG_SECOND) $(shell find $(OBJ)/*/. -maxdepth 1 -type f -regex ".*\.o")  -o $(LIB)/$(SHAREDLIB)

clean:
$(SUBDIRS):
	$(MAKE) -C $@ $(MAKECMDGOALS) clean
#	$(shell rm -f -r $(OBJ)/$@/* $(BIN)/$@ $(LIB)/lib$@.so)

mklb:
$(SUBDIRS):
	$(MAKE) -C $@ $(MAKECMDGOALS) so



test:
	@./$(BIN)/$(TARGET)
	
so:
	@mkdir -p $(OBJ)/$(TARGET)  
	@make -p $(LIB)/$(SHAREDLIB)

arc:
	ar -vr $(LIB)/libD_S.a $(OBJECTS)

