#ifndef SPHERE_H
#define SPHERE_H

#include <math.h>

#include "Mesh.h"

struct Sphere : Mesh {

    Sphere();
    Sphere(float radius);
    Sphere(float radius, float slices, float stacks);

    std::string getObj();

    float radius;
    float slices, stacks;
};

#endif
