# Declaration of variables
CC = g++

LIBS = -lGL -lGLU -lglut -lm -lGLEW
CC_FLAGS = -Wall -Wextra -Wfloat-equal -Wshadow -Wpointer-arith -Wunreachable-code

all: Engine.o EngineState.o Command.o XML.o Models.o FPSCamera.o OrbitalCamera.o fTriple.o 
	$(CC) EngineState.o Command.o Engine.o XML.o Models.o FPSCamera.o OrbitalCamera.o fTriple.o -o Engine $(LIBS)

# debug: Engine.o EngineState.o Command.o XML.o Models.o FPSCamera.o OrbitalCamera.o fTriple.o
# 	$(CC) -g EngineState.o Command.o Engine.o XML.o Models.o FPSCamera.o OrbitalCamera.o fTriple.o -o Engine) $(LIBS)

# To obtain object files
%.o: %.cpp
	$(CC) -c $(CC_FLAGS) $< -o $@

# To remove generated files
clean:
	rm -f Engine *.o
