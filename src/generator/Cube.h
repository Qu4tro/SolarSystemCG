#ifndef CUBE_H
#define CUBE_H

#include <math.h>

#include "Mesh.h"

struct Cube : Mesh {

    Cube();
    Cube(float W, float L, float H, int divisions);
    Cube(float W, float L, float H);

    std::string getObj();

    float width, length, height;
    int partitions;
};

#endif
