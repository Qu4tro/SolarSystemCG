#ifndef CONE_H
#define CONE_H

#include <vector>
#include <math.h>

#include "fTriple.h"
#include "Mesh.h"

struct Cone : Mesh {

    Cone();
    Cone(float radius, float height);
    Cone(float radius, float height, float slices, float stacks);

    std::vector<fTriple> getPoints();

    float radius, height;
    float slices, stacks;
};

#endif
