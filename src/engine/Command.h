#ifndef COMMAND_H
#define COMMAND_H

#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/gl.h>

#include <math.h>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

#include <fTriple.h>

struct Command {
    virtual void apply() = 0;
    virtual std::string toString() = 0;
    virtual ~Command() { }

};

#endif
