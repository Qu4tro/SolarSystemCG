#ifndef PLANE_H
#define PLANE_H

#include <math.h>

#include "Mesh.h"

struct Plane : Mesh {

    Plane();

    std::string getObj();
};

#endif
