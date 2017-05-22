#pragma once

#include <sstream>
#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/gl.h>

#include "Command.h"
#include "../Model.h"

struct DrawModel : Command {

    Model* model;

    DrawModel(Model*);
    void apply();
    std::string toString();
};
