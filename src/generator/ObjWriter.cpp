#include "ObjWriter.h"

ObjWriter::ObjWriter(){

}
 
unsigned ObjWriter::addVertex(float x, float y, float z){
    objStream << "v" << " ";
    objStream << x << " ";
    objStream << y << " ";
    objStream << z << " ";
    objStream << std::endl;
}

unsigned ObjWriter::addNormal(float x, float y, float z){
    objStream << "vn" << " ";
    objStream << x << " ";
    objStream << y << " ";
    objStream << z << " ";
    objStream << std::endl;
}

unsigned ObjWriter::addTexture(float u, float v){
    objStream << "vt" << " ";
    objStream << u << " ";
    objStream << v << " ";
    objStream << std::endl;
}

void ObjWriter::makeTriangle(){
    objStream << "f" << " ";
    objStream << "-3/-3/-3" << " ";
    objStream << "-2/-2/-2" << " ";
    objStream << "-1/-1/-1" << " ";
    objStream << std::endl;
}

std::string ObjWriter::toString(){
    return objStream.str();
}
