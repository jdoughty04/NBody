CC = g++
AR = ar
ARFLAGS = rcs
CFLAGS = --std=c++17 -Wall -Werror -pedantic -g
LIB = -lsfml-graphics -lsfml-audio -lboost_unit_test_framework -lsfml-window -lsfml-system
OBJECTS = CelestialBody.o Universe.o

all: NBody.a NBody test

# Wildcard recipe to make .o files from corresponding .cpp file
%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) $(LIB) -c $<


NBody: main.o $(OBJECTS) 
	$(CC) -g $(CFLAGS) -o $@ $^ -L. -lNBody $(LIB)

NBody.a: $(OBJECTS)
	$(AR) $(ARFLAGS) libNBody.a $^
	$(AR) $(ARFLAGS) NBody.a $^

test: $(OBJECTS) test.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIB)

clean:
	rm *.o *.a NBody test

lint:
	cpplint *.cpp *.hpp
