#include "EnterContext.h"

void EnterContext::apply(){
    glPushMatrix();
}

std::string EnterContext::toString(){
    std::ostringstream stringStream;
    stringStream << "EnterContext";
    stringStream << std::endl;

    return stringStream.str();
}
