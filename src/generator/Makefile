# Declaration of variables
CC = gcc
CC_FLAGS = -Wall -Wextra -Wfloat-equal -Wshadow -Wpointer-arith -Wunreachable-code
LIBS = -lm

# Generator target
generator: generator.o create_models.o
	$(CC) generator.o create_models.o -o Generator $(LIBS)

debug: generator.o create_models.o
	$(CC) -g generator.o create_models.o -o Generator $(LIBS)

# To obtain object files
%.o: %.c
	$(CC) -c $(CC_FLAGS) $< -o $@

# To remove generated files
clean:
	rm -f Generator *.o
