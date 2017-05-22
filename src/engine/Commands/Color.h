#pragma once

#include "Command.h"
#include <sstream>
#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/gl.h>


struct Color : Command {
    float R, G, B;

    Color(float r, float g, float b);
    void apply();
    std::string toString();
};

