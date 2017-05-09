# Declaration of variables
CC = g++
CC_FLAGS = -Wall -Wextra -Wfloat-equal -Wshadow -Wpointer-arith -Wunreachable-code -g
LIBS = -lm

# Generator target
Generator: Gen.o Plane.o Cube.o Sphere.o Cone.o Bezier.o ObjWriter.o fTriple.o 
	$(CC) Gen.o Plane.o Cube.o Sphere.o Cone.o Bezier.o ObjWriter.o fTriple.o -o Generator $(LIBS) $(CC_FLAGS)

# To obtain object files
%.o: %.c
	$(CC) -c $(CC_FLAGS) $< -o $@

# To remove generated files
clean:
	rm -f Generator *.o
