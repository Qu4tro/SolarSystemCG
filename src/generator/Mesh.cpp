#include "Mesh.h"

std::string Mesh::toString(){

    std::stringstream stringStream;
    for(auto it: getPoints()){
        stringStream << it.toLine();
    }

    return stringStream.str();
}
