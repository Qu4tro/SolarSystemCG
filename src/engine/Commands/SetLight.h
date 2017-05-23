#pragma once

#include "Command.h"
#include <sstream>
#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/gl.h>

#include "../fTriple.h"

struct SetLight : Command {
    fTriple point;
    bool isPoint;

    SetLight(fTriple, bool ispoint);
    void apply();
    std::string toString();

};

