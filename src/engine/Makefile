# Declaration of variables
CC = g++

LIBS = -lGL -lGLU -lglut -lm -lGLEW
CC_FLAGS = -Wall -Wfloat-equal -Wshadow -Wpointer-arith -Wunreachable-code -Wno-unused-parameter -g

all: Engine.o EngineState.o Command.o XML.o Models.o FPSCamera.o OrbitalCamera.o fTriple.o
	$(CC) EngineState.o Command.o Engine.o XML.o Models.o FPSCamera.o OrbitalCamera.o fTriple.o -o Engine $(LIBS)

# debug: Engine.o EngineState.o Command.o XML.o Models.o FPSCamera.o OrbitalCamera.o fTriple.o
# 	$(CC) -g EngineState.o Command.o Engine.o XML.o Models.o FPSCamera.o OrbitalCamera.o fTriple.o -o Engine) $(LIBS)

# To obtain object files

# fTriple.o: ../fTriple.cpp
# 	$(CC) -c $(CC_FLAGS) ../fTriple.cpp -o fTriple.o

%.o: %.cpp
	$(CC) -c $(CC_FLAGS) $< -o $@

# To remove generated files
clean:
	rm -f Engine *.o
