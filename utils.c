#include "utils.h"

int nParams(char** params){

    if (params == NULL || *params == NULL){
        return 0; 
    }
    return 1 + nParams(params + 1);
}

char** split(char* string){

    char** strings = NULL;
    char* p = strtok(string, " ");
    int n_spaces = 0;

    while (p) {
        n_spaces++;
        strings = realloc(strings, sizeof(char*) * n_spaces);
    
        if (strings == NULL)
            exit (-1); /* memory allocation failed */
    
        strings[n_spaces - 1] = p;
    
        p = strtok(NULL, " ");
    }

    strings = realloc(strings, sizeof(char*) * (n_spaces + 1));
    strings[n_spaces] = 0;

    return strings;
}

void print_strings(char** strings){
    int i;
    for (i = 0; strings[i] != NULL; ++i) {
        printf("%s\n", strings[i]);
        fflush(stdout);
    }
}

char* strstrip(char* s){

        size_t size;
        char *end;

        size = strlen(s);

        if (!size)
                return s;

        end = s + size - 1;
        while (end >= s && isspace(*end))
                end--;
        *(end + 1) = '\0';

        while (*s && isspace(*s))
                s++;

        return s;
}

char* dupstr (const char* s){

    char *p = malloc(strlen(s) + 1); 

    if (p != NULL){
        strcpy (p,s);
    }

    return p;
}


void printCharBuffer(char* b){ int i; for (i = 0; b[i] != '\0'; ++i) printf("%d ", b[i]); printf("\n");}

