# Declaration of variables
CC = g++

LIBS = -lGL -lGLU -lglut -lm -lGLEW
CC_FLAGS = -Wall -Wextra -Wfloat-equal -Wshadow -Wpointer-arith -Wunreachable-code

# File names
GEN = Generator
ENG = Engine

all: 
	@echo "Invocação é \"make generator\" ou \"make engine\""

# Generator target
generator: generator.o create_models.o
	$(CC) generator.o create_models.o -o $(GEN) $(LIBS)

debug_generator: generator.o create_models.o
	$(CC) -g generator.o create_models.o -o $(GEN) $(LIBS)

# Engine target
engine: Engine.o EngineState.o Command.o XML.o Models.o FPSCamera.o OrbitalCamera.o fTriple.o 
	$(CC) EngineState.o Command.o Engine.o XML.o Models.o FPSCamera.o OrbitalCamera.o fTriple.o -o $(ENG) $(LIBS)

# debug_engine: Engine.o EngineState.o Command.o XML.o Models.o FPSCamera.o OrbitalCamera.o fTriple.o
# 	$(CC) -g EngineState.o Command.o Engine.o XML.o Models.o FPSCamera.o OrbitalCamera.o fTriple.o -o $(ENG) $(LIBS)

# To obtain object files
%.o: %.cpp %.c
	$(CC) -c $(CC_FLAGS) $< -o $@

# To remove generated files
clean:
	rm -f $(GEN) $(ENG) *.o
