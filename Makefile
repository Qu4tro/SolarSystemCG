# Declaration of variables
CC = gcc
CC_FLAGS = -ansi -Wall -Wextra -Wfloat-equal -Wshadow -Wpointer-arith -Wunreachable-code

# File names
EXEC = generator
SOURCES = $(wildcard *.c)
OBJECTS = $(SOURCES:.c=.o)

# Main target
$(EXEC): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(EXEC)

# To obtain object files
%.o: %.c
	$(CC) -c $(CC_FLAGS) $< -o $@

# To remove generated files
clean:
	rm -f $(EXEC) $(OBJECTS)
