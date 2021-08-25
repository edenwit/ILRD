CFLAGS = -ansi -pedantic-errors -Wall -Wextra -g
VPATH = ../include/shape: ../test:../obj
OBJ = shape.o shape_test.o rectangle.o square.o line.o circle.o
INCLUDE = -I ../include/shape
CC = g++

shape.out : $(OBJ)
    $(CC) $(CFLAGS) -o shape.out $(OBJ)
shape.o : shape.cpp shape.hpp
    $(CC) -c $(CFLAGS) -o shape.o ../src/shape/shape.cpp $(INCLUDE)
shape_test.o : shape_test.cpp shape.hpp circle.hpp square.hpp rectangle.hpp line.hpp 
    $(CC) -c $(CFLAGS) -o shape_test.o ../test/shape_test.cpp $(INCLUDE)
circle.o : circle.cpp circle.hpp
    $(CC) -c $(CFLAGS) -o circle.o ../src/shape/circle.cpp $(INCLUDE)
line.o : line.cpp line.hpp
    $(CC) -c $(CFLAGS) -o line.o ../src/shape/line.cpp $(INCLUDE)
square.o : square.cpp square.hpp
    $(CC) -c $(CFLAGS) -o square.o ../src/shape/square.cpp $(INCLUDE)
rectangle.o : rectangle.cpp rectangle.hpp
    $(CC) -c $(CFLAGS) -o rectangle.o ../src/shape/rectangle.cpp $(INCLUDE)


clean :
    rm *.o *.out