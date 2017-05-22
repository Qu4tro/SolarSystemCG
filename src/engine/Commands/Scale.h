#pragma once

#include <sstream>
#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/gl.h>

#include "Command.h"

struct Scale : Command {
    float X, Y, Z;

    Scale(float x, float y, float z);
    void apply();
    std::string toString();
};


