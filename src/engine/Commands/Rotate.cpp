#include "Rotate.h"

Rotate::Rotate(float ang, float x, float y, float z){
    angle = ang;
    axisX = x;
    axisY = y;
    axisZ = z;
}

void Rotate::apply(){
    glRotatef(angle, axisX, axisY, axisZ);
}
std::string Rotate::toString(){
    std::ostringstream stringStream;
    stringStream << "Rotate: ";

    stringStream << "angle=" << angle << " ";
    stringStream << "axisX=" << axisX << " ";
    stringStream << "axisY=" << axisY << " ";
    stringStream << "axisZ=" << axisZ << " ";
    stringStream << std::endl;

    return stringStream.str();
}
