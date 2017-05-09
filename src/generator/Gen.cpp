#include <iostream>
#include <fstream>
#include <string>

#include "Mesh.h"

#include "Plane.h"
#include "Cube.h"
#include "Sphere.h"
#include "Cone.h"
#include "Bezier.h"

void usage(){
    std::cerr << "Model generator.\n\n";
    std::cerr << "Usage:\n";
    std::cerr << "\tgenerator bezier <input.3d> <output.3d>\n";
    std::cerr << "\tgenerator plane <output.3d>\n";
    std::cerr << "\tgenerator box <length> <width> <height> [<divisios>] <output.3d>\n";
    std::cerr << "\tgenerator sphere <radius> <slices> <stacks> <output.3d>\n";
    std::cerr << "\tgenerator cone <bottom radius> <height> <slices> <stacks> <output.3d>\n";
}

Mesh* parse_argv(int argc, char* argv[]){
    std::string model(argv[0]);
    --argc; ++argv;
    Mesh* mesh;

    if (model == "plane"){
        mesh = new Plane();

    } else if (model == "bezier"){
        assert(argc == 1 && "Tem de conter um e só um input file");
        std::string filename(argv[0]);
        mesh = new Bezier(filename);

    } else if (model == "box"){
        if (argc == 0){
            mesh = new Cube();
        } else if (argc == 3){
            mesh = new Cube(atof(argv[0]), atof(argv[1]), atof(argv[2]));
        } else if (argc == 4){
            mesh = new Cube(atof(argv[0]), atof(argv[1]), atof(argv[2]), atoi(argv[3]));
        } else {
            usage();
        }

    } else if (model == "sphere"){
        if (argc == 0){
            mesh = new Sphere();
        } else if (argc == 1){
            mesh = new Sphere(atof(argv[0]));
        } else if (argc == 3){
            mesh = new Sphere(atof(argv[0]), atoi(argv[1]), atoi(argv[2]));
        } else {
            usage();
        }

    } else if (model == "cone"){
        if (argc == 0){
            mesh = new Cone();
        } else if (argc == 2){
            mesh = new Cone(atof(argv[0]), atof(argv[1]));
        } else if (argc == 4){
            mesh = new Cone(atof(argv[0]), atof(argv[1]), atoi(argv[2]), atoi(argv[3]));
        } else {
            usage();
        }

    }

    return mesh;
}



int main(int argc, char* argv[]){
    --argc; ++argv;

    std::string filename(argv[--argc]);
    std::ofstream output(filename);
    Mesh* mesh = parse_argv(argc, argv);

    output << mesh -> getObj();

    return 0;
}
