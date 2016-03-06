#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#ifndef UTILS_H
#define UTILS_H

int nParams(char** params);

char** split(char* string);

void print_strings(char** strings);

char* strstrip(char *s);

void printCharBuffer(char* b);

#endif
