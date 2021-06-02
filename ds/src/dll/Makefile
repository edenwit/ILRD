TARGET 	= dll

SRC		= .
INCLUDE	= ../../include
TEST		= ../../test
OBJ 		= ../../obj/$(TARGET)
BIN		= ../../bin
LIB		= ../../lib

CC 		= gcc
CFLAGS		= -ansi -pedantic-errors -fPIC -Wall -Wextra -g -I$(INCLUDE)
LDFLAGS	= -shared

TARGET_LIB	= $(TARGET)# target lib

VLG		= valgrind --leak-check=yes --track-origins=yes
CGDB		= cgdb

HEADERS	= $(INCLUDE)/$(TARGET).h 
SOURCES	= $(TEST)/$(TARGET)_test.c $(SRC)/$(TARGET).c 
OBJECT		= $(OBJ)/$(TARGET).o #$(OBJ)/$(TARGET)_test.o 


$(BIN)/$(TARGET): $(LIB)/lib$(TARGET_LIB).so $(OBJ)/$(TARGET)_test.o 
	$(CC) $(CFLAGS) $(LIB)/lib$(TARGET_LIB).so $(OBJ)/$(TARGET)_test.o  -o $@ -Wl,-rpath=$(LIB) -L$(LIB) -l$(TARGET_LIB)

#$ cc $SRCS –Wl,-rpath=/home/beazley/libs \ -L/home/beazleys/libs -lfoo


$(LIB)/lib$(TARGET_LIB).so: $(OBJECT) $(HEADERS)
	@mkdir -p $(LIB)
	$(CC) $(OBJECT) -o $@ ${LDFLAGS} 
	
$(OBJ)/%.o : $(SRC)/%.c
	@mkdir -p $(OBJ)
	$(CC) $(CFLAGS) -c $^ -o $@
	
$(OBJ)/%.o : $(TEST)/%.c 
	@mkdir -p $(OBJ)
	$(CC) $(CFLAGS) -c $^ -o $@				

.PHONY: clean run tree cgdb print 

run :
	$(BIN)/$(TARGET)

clean : 
	rm -f $(BIN)/$(TARGET)
	rm -f $(OBJ)/*.o
	rm -f $(LIB)/$(TARGET).so	
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

