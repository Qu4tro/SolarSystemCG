#ifndef MESH_H
#define MESH_H

#include <sstream>
#include <string>
#include <vector>

#include "ObjWriter.h"

struct Mesh {
    virtual ~Mesh() { }

    virtual std::string getObj() = 0;
};


#endif
