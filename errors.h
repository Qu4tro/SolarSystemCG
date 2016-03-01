#ifndef ERRORS_H
#define ERRORS_H

#include <stdio.h>

#define NO_ERROR 0
#define INVALID_ARGS 1

#define NOT_POSITIVE_INTEGER 10
#define FILE_DOES_NOT_EXIST 11
#define UNREADABLE_FILE 12
#define CANT_OPEN_INPUT_FILE 14
#define WRONG_NFIELDS_SALES 15
#define GOT_NULL_TO_TOKEN 16


void print_error(int error);


#endif

