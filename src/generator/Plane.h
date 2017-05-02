#ifndef PLANE_H
#define PLANE_H

#include <vector>
#include <math.h>

#include "Mesh.h"
#include "fTriple.h"

struct Plane : Mesh {

    Plane();

    std::vector<fTriple> getPoints();
};

#endif
