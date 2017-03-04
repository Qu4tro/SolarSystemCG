#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "errors.h"
#include "create_models.h"

void usage(){
    fprintf(stderr, "Model generator. \n"
                    "\n"
                    "Usage:\n"
                    "  generator plane <output.3d>\n"
                    "  generator box <length> <width> <height> [<divisios>] <output.3d>\n"
                    "  generator sphere <radius> <slices> <stacks> <output.3d>\n"
                    "  generator cone <bottom radius> <height> <slices> <stacks> <output.3d>\n"
           );
}

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

    if (strcmp(model, "plane") == 0 && n_args == 1){
            return NO_ERROR;
    }

    if (strcmp(model, "box") == 0 && (n_args == 4 || n_args == 5) &&
        is_positive_float(argv[0]) &&
        is_positive_float(argv[1]) &&
        is_positive_float(argv[2])){
      if (is_positive_int(argv[3]) || n_args == 4){
        return NO_ERROR;
      }
    }

    if ((strcmp(model, "sphere") == 0 && n_args == 4) &&
        is_positive_float(argv[0]) &&
        is_positive_int(argv[1]) &&
        is_positive_int(argv[2])){
            return NO_ERROR;
    }

    if ((strcmp(model, "cone") == 0 && n_args == 5) &&
        is_positive_float(argv[0]) &&
        is_positive_float(argv[1]) &&
        is_positive_int(argv[2]) &&
        is_positive_int(argv[3])){
            return NO_ERROR;
    }

    return INVALID_ARGS;
}

void fprint_vertices(FILE* f, float* vertices, int n){

    int i;
    for (i = 0; i < n; ++i) {

        fprintf(f, "%f", vertices[i]);  

        if (i != n - 1){

            if (i % 3 == 2) {
                fprintf(f, "\n");
            } else {
                fprintf(f, " ");

            }
        }
    }
}

int main(int argc, char* argv[]){

    int err;

    char* model;
    float* vertices = calloc(sizeof(float), 500000); //TODO
    int nVertices;

    char* filename;
    FILE* output;


    if ((err = validate_args(--argc, ++argv))){
        usage();
        return -1;
    }
    model = argv[0];
    --argc; ++argv;

    if        (strcmp(model, "plane")  == 0){
        nVertices = create_plane(vertices);
        filename = argv[0];

    } else if (strcmp(model, "box")    == 0){
      if (argc == 4){
        nVertices = create_box(vertices, atof(argv[0]), atof(argv[1]), atof(argv[2]), 1);
        filename = argv[3];
      } else {
        nVertices = create_box(vertices, atof(argv[0]), atof(argv[1]), atof(argv[2]), atoi(argv[3]));
        filename = argv[4];
      }

    } else if (strcmp(model, "sphere") == 0){
        nVertices = create_sphere(vertices, atof(argv[0]), atoi(argv[1]), atoi(argv[2]));
        filename = argv[3];

    } else if (strcmp(model, "cone")   == 0){
        nVertices = create_cone(vertices, atof(argv[0]), atof(argv[1]), atoi(argv[2]), atoi(argv[3]));
        filename = argv[4];
    }

    assert(nVertices % 3 == 0);

    output = fopen(filename, "w");

    fprint_vertices(output, vertices, nVertices*3);

    return 0;
}
