#include "Color.h"

Color::Color(float r, float g, float b){
    R = r;
    G = g;
    B = b;
}

void Color::apply(){
    glColor3f(R, G, B);
}

std::string Color::toString(){
    std::ostringstream stringStream;
    stringStream << "Color: ";
    stringStream << "R=" << R << " ";
    stringStream << "G=" << G << " ";
    stringStream << "B=" << B << " ";
    stringStream << std::endl;

    return stringStream.str();
}

