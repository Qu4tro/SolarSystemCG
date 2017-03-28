#ifndef COMMAND_H
#define COMMAND_H

#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/gl.h>


#include <memory>
#include <sstream>
#include <string>
#include <vector>

struct Command {
    virtual void apply() = 0;
    virtual std::string toString() = 0;
    virtual ~Command() { }

};

#endif
