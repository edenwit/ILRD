# Developer: Eden Wittenberg;									
#   Status: done;												
#   Date Of Creation: 02.06.21;									
#   Date Of Approval:											
#   Approved By: ;												
#   Description: Makefile;			            	*/

NAME = data_structures
LDIR = ../lib
TDIR = ../test
ODIR = ../obj
IDIR = ../include
SDIR = ../src
BIN  = ../bin
SRCS = $(shell find $(SDIR) -type f -name "*.c")
OBJS_DEBUG = $(addprefix $(ODIR)/,$(patsubst %.c,%_DEBUG.o,$(notdir $(SRCS))))
OBJS_RELEASE = $(addprefix $(ODIR)/,$(patsubst %.c,%_RELEASE.o,$(notdir $(SRCS))))
DEBUG = -g
RELEASE = -DNDEBUG -O3
TESTS_SRC = $(wildcard $(TDIR)/*.c)
TESTS = $(patsubst %.c,%.out,$(TESTS_SRC))
CC = gcc -ansi -pedantic-errors -Wall -Wextra -I $(IDIR) -fPIC	

#auto dependency
deps := $(patsubst %.o,%.d,$(OBJS)) 
-include $(deps)
DEPFLAGS = -MMD -MF $(@:.o=.d)

##########################################################################################################

# default which creates both debug and release version
all: debug release	

##########################################################################################################
#creates executibles for each test in datastructures directory and runs them, also will build debug library if necessary
test: $(TESTS)

$(BIN): $(TESTS_SRC) debug
	$(CC) $(SHARED_OBJ_PATH) $(patsubst %.out,%.c,$(TESTS)) -o $@ -L $(LDIR) $(LDIR)/lib_$(NAME)_DEBUG.so
	$@
############################################################################################################
#builds debug version
debug: $(LDIR)/lib_$(NAME)_DEBUG.so

$(LDIR)/lib_$(NAME)_DEBUG.so: $(OBJS_DEBUG)
	$(CC) -shared -o $@ $(OBJS_DEBUG)

$(ODIR)/%_DEBUG.o: $(SDIR)/*/%.c
	echo $<
	$(CC) -c $(DEBUG) $< -o $@ $(DEPFLAGS)	
#############################################################################################################
#builds release version	
release: $(LDIR)/lib_$(NAME)_RELEASE.so

$(LDIR)/lib_$(NAME)_RELEASE.so: $(OBJS_RELEASE)
	$(CC) -shared -o $@ $(OBJS_RELEASE)
	
$(ODIR)/%_RELEASE.o: $(SDIR)/*/%.c 
	$(CC) -c $(RELEASE) $< -o $@ $(DEPFLAGS)	

############################################################################################################
#Utilities
.PHONY: clean all release debug test

clean:
	rm $(TESTS) $(ODIR)/*.o $(LIBDIR)/*.so
