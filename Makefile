# Declaration of variables
CC = gcc

LIBS = -lGL -lGLU -lglut -lm 
CC_FLAGS = -Wall -Wextra -Wfloat-equal -Wshadow -Wpointer-arith -Wunreachable-code

XML = -I/usr/include/libxml2 -lxml2 -lz -lm -ldl

# File names
GEN = generator
ENG = engine

SOURCES = $(wildcard *.c)
OBJECTS = $(SOURCES:.c=.o)

all: 
	@echo "Invocação é \"make generator\" ou \"make engine\""

# Generator target
$(GEN): generator.o errors.o create_models.o
	$(CC) generator.o errors.o create_models.o -o $(GEN) $(LIBS)

# Engine target
$(ENG): xmlParser.o engine.o errors.o utils.o 
	$(CC) engine.o errors.o utils.o xmlParser.o -o $(ENG) $(LIBS) $(XML)

# To obtain object files
%.o: %.c
	$(CC) -c $(CC_FLAGS) $(XML) $< -o $@

# To remove generated files
clean:
	rm -f $(GEN) $(ENG) $(OBJECTS)
