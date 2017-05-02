#ifndef SPHERE_H
#define SPHERE_H

#include <vector>
#include <math.h>

#include "fTriple.h"
#include "Mesh.h"

struct Sphere : Mesh {

    Sphere();
    Sphere(float radius);
    Sphere(float radius, float slices, float stacks);

    std::vector<fTriple> getPoints();

    float radius;
    float slices, stacks;
};

#endif
