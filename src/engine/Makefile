# Declaration of variables
CC = g++

LIBS = -lGL -lGLU -lglut -lm -lGLEW
CC_FLAGS = -Wall -Wfloat-equal -Wshadow -Wpointer-arith -Wunreachable-code -Wno-unused-parameter -g

COMMANDS = EnterContext.o ExitContext.o Color.o Scale.o Translate.o TranslateT.o Rotate.o RotateT.o DrawModel.o DrawModelVBO.o Command.o
MODELS = Model_3D.o
CAMERAS = FPSCamera.o OrbitalCamera.o 

all: Engine.o EngineState.o SceneParser.o tinyxml2.o fTriple.o $(COMMANDS) $(MODELS) $(CAMERAS)
	$(CC) EngineState.o Engine.o SceneParser.o tinyxml2.o fTriple.o $(COMMANDS) $(MODELS) $(CAMERAS) -o Engine $(LIBS) $(CC_FLAGS)

# debug: Engine.o EngineState.o Command.o XML.o Models.o FPSCamera.o OrbitalCamera.o fTriple.o
# 	$(CC) -g EngineState.o Command.o Engine.o XML.o Models.o FPSCamera.o OrbitalCamera.o fTriple.o -o Engine) $(LIBS)

# To obtain object files

# fTriple.o: ../fTriple.cpp
# 	$(CC) -c $(CC_FLAGS) ../fTriple.cpp -o fTriple.o

%.o: Commands/%.cpp
	$(CC) -c $(CC_FLAGS) $< -o $@

%.o: %.cpp
	$(CC) -c $(CC_FLAGS) $< -o $@

# To remove generated files
clean:
	rm -f Engine *.o
