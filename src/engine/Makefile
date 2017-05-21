# Declaration of variables
CC = g++

LIBS = -lGL -lGLU -lglut -lm -lGLEW
CC_FLAGS = -Wall -Wfloat-equal -Wshadow -Wpointer-arith -Wunreachable-code -Wno-unused-parameter -g

all: Engine.o EngineState.o Command.o SceneParser.o tinyxml2.o Model.o FPSCamera.o OrbitalCamera.o fTriple.o
	$(CC) EngineState.o Command.o Engine.o SceneParser.o tinyxml2.o Model.o FPSCamera.o OrbitalCamera.o fTriple.o -o Engine $(LIBS)

%.o: %.cpp
	$(CC) -c $(CC_FLAGS) $< -o $@

# To remove generated files
clean:
	rm -f Engine *.o
