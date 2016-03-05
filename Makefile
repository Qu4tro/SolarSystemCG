# Declaration of variables
CC = gcc

LIBS = -lGL -lGLU -lglut -lm 
CC_FLAGS = -Wall -Wextra -Wfloat-equal -Wshadow -Wpointer-arith -Wunreachable-code

# File names
GEN = generator
ENG = engine

SOURCES = $(wildcard *.c)
OBJECTS = $(SOURCES:.c=.o)

# Generator target
$(GEN): generator.o errors.o create_models.o
	$(CC) generator.o errors.o create_models.o -o $(GEN)

# Engine target
$(ENG): engine.o errors.o utils.o
	$(CC) engine.o errors.o utils.o -o $(ENG) $(LIBS)

# To obtain object files
%.o: %.c
	$(CC) -c $(CC_FLAGS) $< -o $@

# To remove generated files
clean:
	rm -f $(GEN) $(ENG) $(OBJECTS)
