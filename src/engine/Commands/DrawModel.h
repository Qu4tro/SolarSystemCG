#pragma once

#include <assert.h>
#include <sstream>
#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/gl.h>

#include "Command.h"
#include "../Model_3D.h"

struct DrawModel : Command {

    Model_3D model;

    DrawModel();
    DrawModel(Model_3D);
    void apply();
    std::string toString();
};
