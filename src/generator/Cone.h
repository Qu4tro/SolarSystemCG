#ifndef CONE_H
#define CONE_H

#include <math.h>

#include "Mesh.h"

struct Cone : Mesh {

    Cone();
    Cone(float radius, float height);
    Cone(float radius, float height, float slices, float stacks);

    std::string getObj();

    float radius, height;
    float slices, stacks;
};

#endif
