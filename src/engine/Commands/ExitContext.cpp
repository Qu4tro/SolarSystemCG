#include <sstream>
#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/gl.h>

#include "ExitContext.h"

void ExitContext::apply(){
    glPopMatrix();
}

std::string ExitContext::toString(){
    std::ostringstream stringStream;
    stringStream << "ExitContext";
    stringStream << std::endl;

    return stringStream.str();
}
