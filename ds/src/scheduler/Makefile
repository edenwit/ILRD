# Target name.
TARGET = $(notdir $(shell pwd))


# directories.
OBJDIR = ../../obj
LIBDIR = ../../lib
INCDIR = ../../include

# Compilation details.
CC = gcc
CFLAGS = -ansi -pedantic-errors -Wall -Wextra -g
RFLAGS = -ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3
LDFLAGS = -L$(LIBDIR) -Wl,-rpath=$(LIBDIR)


# List of object file names
OBJNAMES = $(TARGET).o $(TARGET)_test.o

# List of object file paths.
OBJECTS = $(addprefix $(OBJDIR)/, $(OBJNAMES))

.PHONY: clean all test debug release test_ r

all: $(LIBDIR)/lib$(TARGET).so a.out

$(LIBDIR)/lib$(TARGET).so: $(OBJDIR)/$(TARGET).o
	$(CC) -shared $< -o $@
	
a.out: $(OBJDIR)/$(TARGET)_test.o
	$(CC)  $^ -o $@ $(LDFLAGS) -l$(TARGET)
	
$(OBJDIR)/$(TARGET).o: $(TARGET).c  $(TARGET).h
	$(CC) $(CFLAGS) -fpic -c $< -o $@ -I $(INCDIR)
	
$(OBJDIR)/$(TARGET)_test.o: $(TARGET)_test.c $(TARGET).h
	$(CC) $(CFLAGS) -c $< -o $@ -I $(INCDIR)

release: $(LIBDIR)/lib$(TARGET)_R.so $(TARGET)_R

$(LIBDIR)/lib$(TARGET)_R.so: $(OBJDIR)/$(TARGET)_R.o
	$(CC) -shared $< -o $@
	
$(TARGET)_R: $(OBJDIR)/$(TARGET)_test_R.o
	$(CC) $(LDFLAGS) $^ -o $@ -l$(TARGET)
	
$(OBJDIR)/$(TARGET)_R.o: $(TARGET).c  $(TARGET).h
	$(CC) $(RFLAGS) -fpic -c $< -o $@ -I $(INCDIR)
	
$(OBJDIR)/$(TARGET)_test_R.o: $(TARGET)_test.c $(TARGET).h
	$(CC) $(RFLAGS) -c $< -o $@ -I $(INCDIR)

test: a.out
	./a.out
	
test_ r: $(TARGET)_R
	./$(TARGET)_R

clean:
	rm a.out $(OBJECTS)

