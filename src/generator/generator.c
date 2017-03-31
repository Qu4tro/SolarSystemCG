#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

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
        return 1;
    } else {
        model = argv[0];
        argv++;
        n_args--;
    }

    if (strcmp(model, "plane") == 0 && n_args == 1){
            return 0;
    }

    if (strcmp(model, "box") == 0 && (n_args == 4 || n_args == 5) &&
        is_positive_float(argv[0]) &&
        is_positive_float(argv[1]) &&
        is_positive_float(argv[2])){
      if (is_positive_int(argv[3]) || n_args == 4){
        return 0;
      }
    }

    if ((strcmp(model, "sphere") == 0 && n_args == 4) &&
        is_positive_float(argv[0]) &&
        is_positive_int(argv[1]) &&
        is_positive_int(argv[2])){
            return 0;
    }

    if ((strcmp(model, "cone") == 0 && n_args == 5) &&
        is_positive_float(argv[0]) &&
        is_positive_float(argv[1]) &&
        is_positive_int(argv[2]) &&
        is_positive_int(argv[3])){
            return 0;
    }

    return 1;
}

int main(int argc, char* argv[]){
    char* model;

    char* filename;
    FILE* output;


    if (validate_args(--argc, ++argv)){
        usage();
        return -1;
    }
    model = argv[0];
    --argc; ++argv;
    filename = argv[--argc];

    output = fopen(filename, "w");

    if        (strcmp(model, "plane")  == 0){
        create_plane(output);
        filename = argv[0];

    } else if (strcmp(model, "box")    == 0){
      if (argc == 3){
        create_box(output, atof(argv[0]), atof(argv[1]), atof(argv[2]), 1);
      } else {
        create_box(output, atof(argv[0]), atof(argv[1]), atof(argv[2]), atoi(argv[3]));
      }

    } else if (strcmp(model, "sphere") == 0){
        create_sphere(output, atof(argv[0]), atoi(argv[1]), atoi(argv[2]));

    } else if (strcmp(model, "cone")   == 0){
        create_cone(output, atof(argv[0]), atof(argv[1]), atoi(argv[2]), atoi(argv[3]));
    }


    return 0;
}
