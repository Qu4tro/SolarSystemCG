#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "errors.h"
#include "create_models.h"

int is_positive_int(char* str){
    int n = atoi(str);
    return (n > 0);
}
int is_positive_float(char* str){
    float n = atof(str);
    return (n > 0);
}
int is_nonzero_float(char* str){
    float n = atof(str);
    return n;
}

int validate_args(int n_args, char* argv[]){

    char* model;

    if (n_args < 1){
        return INVALID_ARGS;
    } else {
        model = argv[0];

        argv++;
        n_args--;
    }

    if (strcmp(model, "plane") == 0 && n_args == 0){
            return NO_ERROR; 
    }

    if ((strcmp(model, "box") == 0 && n_args == 6) &&
        is_positive_float(argv[0]) &&
        is_positive_float(argv[1]) &&
        is_positive_float(argv[2])){
            return NO_ERROR; 
    }

    if ((strcmp(model, "sphere") == 0 && n_args == 6) &&
        is_positive_float(argv[0]) &&
        is_positive_int(argv[1]) &&
        is_positive_int(argv[2])){
            return NO_ERROR; 
    }

    if ((strcmp(model, "cone") == 0 && n_args == 7) &&
        is_positive_float(argv[0]) &&
        is_positive_float(argv[1]) &&
        is_positive_int(argv[2]) &&
        is_positive_int(argv[3])){
            return NO_ERROR; 
    }

    return INVALID_ARGS;
}

void print_vertices(float* vertices, int n){

    int i;
    for (i = 0; i < n; ++i) {

        printf("%f", vertices[i]);  

        if (i != n - 1){

            if (i % 3 == 2) {
                if (i % 9 == 8){
                    printf("\n"); 
                }
                printf("\n");

            } else {
                printf(" ");

            }
        }
    }
}

int main(int argc, char* argv[]){
    
    int err;

    char* model;
    float* vertices = NULL;
    int nVertices;

    if ((err = validate_args(--argc, ++argv))){
        printf("Invalid args!");
    }
    model = argv[0];
    --argc; ++argv;

    if        (strcmp(model, "plane")  == 0){
        vertices = create_plane();

    } else if (strcmp(model, "box")    == 0){
        vertices = create_box(atof(argv[0]), atof(argv[1]), atof(argv[2]));

    } else if (strcmp(model, "sphere") == 0){
        vertices = create_sphere(atof(argv[0]), atoi(argv[1]), atoi(argv[2]));
        
    } else if (strcmp(model, "cone")   == 0){
        vertices = create_cone(atof(argv[0]), atof(argv[1]), atoi(argv[2]), atoi(argv[3]));
    } 

    nVertices = vertices[0];
    assert(nVertices % 3 == 0);
    /* int vertices[] = {18, 1, 1, 1, 1, 0, 0, 1, 0, 1, 1, 1, 1, 1, 0, 0, 1, 0, 1}; */

    print_vertices(vertices + 1, vertices[0]);

    return 0;
}
