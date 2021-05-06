
TARGET = $(notdir ${PWD})
SRC = .
BIN = ../../bin
INC = ../../include
OBJ = ../../obj/$(TARGET)
LIB = ../../lib
TEST = ../../test

CC = gcc
#gd flags
CFLAGS = -ansi -pedantic-errors -Wall -Wextra -g -I$(INC)
LDFLAGS = -L$(LIB)

$(BIN)/$(TARGET) : $(OBJ)/queue_test.o  $(OBJ)/queue.o $(OBJ)/sll.o
	$(CC) $(CFLAGS) $^ -o $@  $(LDFLAGS)
 	
$(OBJ)/queue_test.o : $(TEST)/queue_test.c $(INC)/queue.h 
	$(CC) $(CFLAGS) -c $< -o $@
        
$(OBJ)/queue.o : $(SRC)/queue.c $(OBJ)/sll.o $(INC)/queue.h  $(INC)/sll.h 
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ)/sll.o : ../sll/sll.c $(INC)/sll.h 
	$(CC) $(CFLAGS) -c $< -o $@

run:
	./$(BIN)/$(TARGET)
