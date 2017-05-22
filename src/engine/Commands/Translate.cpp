#include "Translate.h"

Translate::Translate(float x, float y, float z){
    X = x;
    Y = y;
    Z = z;
}

void Translate::apply(){
    glTranslatef(X, Y, Z);
}


std::string Translate::toString(){
    std::ostringstream stringStream;
    stringStream << "Translate: ";
    stringStream << "X=" << X << " ";
    stringStream << "Y=" << Y << " ";
    stringStream << "Z=" << Z << " ";
    stringStream << std::endl;

    return stringStream.str();
}
