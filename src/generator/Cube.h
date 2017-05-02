#ifndef CUBE_H
#define CUBE_H

#include <vector>
#include <math.h>

#include "fTriple.h"
#include "Mesh.h"

struct Cube : Mesh {

    Cube();
    Cube(float W, float L, float H, int divisions);
    Cube(float W, float L, float H);

    std::vector<fTriple> getPoints();

    float width, length, height;
    int partitions;
};

#endif
