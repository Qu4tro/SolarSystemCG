#pragma once

#include <sstream>
#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/gl.h>

#include "Command.h"

struct EnterContext : Command {
    void apply();
    std::string toString();
};
