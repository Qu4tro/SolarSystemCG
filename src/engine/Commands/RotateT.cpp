#include "RotateT.h"

RotateT::RotateT(float p, float x, float y, float z){
    period = p;
    axisX = x;
    axisY = y;
    axisZ = z;
}

void RotateT::apply(){
    /* float angle = fmod((glutGet(GLUT_ELAPSED_TIME) / 1000.0f ) * (360.0f / period), 360.0f); */
    float angle = fmod((glutGet(GLUT_ELAPSED_TIME) * 360.0f ) / (period * 1000.0f), 360.0f);
    glRotatef(angle, axisX, axisY, axisZ);
}

std::string RotateT::toString(){
    std::ostringstream stringStream;
    stringStream << "RotateT: ";

    stringStream << "time="   << period << " ";
    stringStream << "axisX="  << axisX  << " ";
    stringStream << "axisY="  << axisY  << " ";
    stringStream << "axisZ="  << axisZ  << " ";
    stringStream << std::endl;

    return stringStream.str();
}
