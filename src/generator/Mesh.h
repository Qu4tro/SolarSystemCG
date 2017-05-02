#ifndef MESH_H
#define MESH_H

#include <sstream>
#include <string>
#include <vector>
#include "fTriple.h"

struct Mesh {
    virtual ~Mesh() { }

    virtual std::vector<fTriple> getPoints() = 0;

    std::string toString();
};


#endif
