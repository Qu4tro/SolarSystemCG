#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef UTILS_H
#define UTILS_H

int nParams(char** params);

char** split(char* string);

char* strstrip(char *s);

char* dupstr(const char *s);

void printCharBuffer(char* b);

int max(int a, int b);

#endif
