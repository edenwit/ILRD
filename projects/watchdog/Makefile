TARGET 	= watchdog

SRC		= .
INCLUDE	= ../../ds/include
TEST	= .
OBJ 	= ./obj
BIN		= .
VECTOR     = ../../ds/src/vector
HEAP = ../../ds/src/heap
PRIORITY_QUEUE = ../../ds/src/heap_priority_queue
UID = ../../ds/src/uid
TASK = ../../ds/src/task
SCHEDULER = ../../ds/src/heap_scheduler
LDFLAGS = -Wl,-rpath=./ -L./ -lwatchdog -lpthread

CC 		= gcc
CFLAGS	= -ansi -pedantic-errors -Wall -Wextra -g -I$(INCLUDE) -fPIC


HEADERS	= $(TARGET).h $(INCLUDE)/heap.h $(INCLUDE)/vector.h \
		  $(INCLUDE)/heap_priority_queue.h $(INCLUDE)/uid.h $(INCLUDE)/task.h \
		  $(INCLUDE)/heap_scheduler.h
			
SOURCES_WATCHDOG = $(UID)/uid.c $(TASK)/task.c $(PRIORITY_QUEUE)/heap_priority_queue.c \
		    	   $(SCHEDULER)/heap_scheduler.c $(TARGET).c $(TARGET)_exe.c
		  
SOURCES_USER = $(UID)/uid.c $(TASK)/task.c $(PRIORITY_QUEUE)/heap_priority_queue.c \
		       $(SCHEDULER)/heap_scheduler.c $(TARGET).c $(TARGET)_test.c

OBJECT_WATCHDOG	= $(OBJ)/vector.o $(OBJ)/heap.o \
		 		  $(OBJ)/heap_priority_queue.o $(OBJ)/uid.o $(OBJ)/task.o \
				  $(OBJ)/heap_scheduler.o $(OBJ)/$(TARGET)_exe.o $(OBJ)/$(TARGET).o

$(BIN)/$(TARGET)_test: $(OBJ)/$(TARGET)_test.o libwatchdog.so $(HEADERS) 
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS)
	
$(BIN)/$(TARGET): libwatchdog.so $(HEADERS) 
	$(CC) $(CFLAGS) $(OBJECT_WATCHDOG) -o $@ $(LDFLAGS)
	
libwatchdog.so: $(OBJECT_WATCHDOG)
	$(CC) -shared -o $@ $^

$(OBJ)/%.o : $(SRC)/%.c
	@mkdir -p $(OBJ)
	$(CC) $(CFLAGS) -c $^ -o $@

$(OBJ)/%.o : $(VECTOR)/%.c 
	@mkdir -p $(OBJ)
	$(CC) $(CFLAGS) -c $^ -o $@
	
$(OBJ)/%.o : $(HEAP)/%.c 
	@mkdir -p $(OBJ)
	$(CC) $(CFLAGS) -c $^ -o $@
	
$(OBJ)/%.o : $(PRIORITY_QUEUE)/%.c 
	@mkdir -p $(OBJ)
	$(CC) $(CFLAGS) -c $^ -o $@
	
$(OBJ)/%.o : $(UID)/%.c 
	@mkdir -p $(OBJ)
	$(CC) $(CFLAGS) -c $^ -o $@
	
$(OBJ)/%.o : $(TASK)/%.c 
	@mkdir -p $(OBJ)
	$(CC) $(CFLAGS) -c $^ -o $@
	
$(OBJ)/%.o : $(TEST)/%.c 
	@mkdir -p $(OBJ)
	$(CC) $(CFLAGS) -c $^ -o $@
	
$(OBJ)/%.o : $(SCHEDULER)/%.c 
	@mkdir -p $(OBJ)
	$(CC) $(CFLAGS) -c $^ -o $@

.PHONY: clean run 

run :
	$(BIN)/$(TARGET)_test

clean : 
	rm -f $(BIN)/$(TARGET)
	rm -f $(BIN)/$(TARGET)_test
	rm -f $(OBJ)/*.o
	rm -r $(OBJ)
	rm -f libwatchdog.so

all: $(BIN)/$(TARGET)_test $(BIN)/$(TARGET)

release: CFLAGS = -ansi -pedantic-errors -Wall -Wextra -I$(INCLUDE) -fPIC -DNDEBUG
release: all

