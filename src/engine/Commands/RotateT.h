#pragma once

#include <sstream>
#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <math.h>

#include "Command.h"

struct RotateT : Command {
    float period;
    float axisX, axisY, axisZ;

    RotateT(float p, float x, float y, float z);
    void apply();
    std::string toString();
};

