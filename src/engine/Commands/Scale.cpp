#include "Scale.h"

Scale::Scale(float x, float y, float z){
    X = x;
    Y = y;
    Z = z;
}

void Scale::apply(){
    glScalef(X, Y, Z);
}
std::string Scale::toString(){
    std::ostringstream stringStream;
    stringStream << "Scale: ";
    stringStream << "X=" << X << " ";
    stringStream << "Y=" << Y << " ";
    stringStream << "Z=" << Z << " ";
    stringStream << std::endl;

    return stringStream.str();
}
