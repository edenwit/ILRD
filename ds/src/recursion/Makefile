TARGET 	= recursion

SRC		= .
INCLUDE	= ../../include
TEST	= ../../test
OBJ 	= ../../obj/$(TARGET)
BIN		= ../../bin
STACK_DIR = ../stack
STACK_TARGET = stack
STACK_OBJ = ../../obj/$(STACK_TARGET)


CC 		= gcc
CFLAGS	= -ansi -pedantic-errors -Wall -Wextra -g -I$(INCLUDE)

VLG		= valgrind --leak-check=yes --track-origins=yes
CGDB	= cgdb

HEADERS	= $(INCLUDE)/$(TARGET).h $(INCLUDE)/$(STACK_TARGET).h 
SOURCES	= $(TEST)/$(TARGET)_test.c $(SRC)/$(TARGET).c $(STACK_DIR)/$(STACK_TARGET).c
OBJECT	= $(OBJ)/$(TARGET).o $(OBJ)/$(TARGET)_test.o $(STACK_OBJ)/$(STACK_TARGET).o

$(BIN)/$(TARGET): $(OBJECT) $(HEADERS) 
	$(CC) $(CFLAGS) $(OBJECT) -o $@  

$(OBJ)/%.o : $(SRC)/%.c
	@mkdir -p $(OBJ)
	$(CC) $(CFLAGS) -c $^ -o $@
	
$(OBJ)/%.o : $(TEST)/%.c 
	@mkdir -p $(OBJ)
	$(CC) $(CFLAGS) -c $^ -o $@				

$(STACK_OBJ)/$(STACK_TARGET).o : $(STACK_DIR)/$(STACK_TARGET).c 
	@mkdir -p $(STACK_OBJ)
	$(CC) $(CFLAGS) -c $^ -o $@		


.PHONY: clean run tree cgdb print 

run :
	$(BIN)/$(TARGET)

clean : 
	rm -f $(BIN)/$(TARGET)
	rm -f $(OBJ)/*.o
	rm -r $(OBJ)
	
tree:
	@tree ../../

vlg :
	@$(VLG) ./$(BIN)/$(TARGET)	

cgdb :
	@$(CGDB) ./$(BIN)/$(TARGET)

print :
	@echo "Sources: $(SOURCES)"
	@echo "Objects: $(OBJECT)"
	@echo "Headers: $(HEADERS)"
				
	


	
	
	
	
