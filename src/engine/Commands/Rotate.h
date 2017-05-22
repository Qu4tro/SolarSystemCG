#pragma once

#include <sstream>
#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include "Command.h"

struct Rotate : Command {
    float angle, axisX, axisY, axisZ;

    Rotate(float ang, float x, float y, float z);
    void apply();
    std::string toString();
};

