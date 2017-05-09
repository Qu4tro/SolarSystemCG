#include "Plane.h"

Plane::Plane(){

}

std::string Plane::getObj(){

    ObjWriter obj;

    obj.addVertex(100, 0, 100);
    obj.addVertex(100, 0, -100);
    obj.addVertex(-100, 0, -100);
    obj.makeTriangle();

    obj.addVertex(100, 0, 100);
    obj.addVertex(-100, 0, 100);
    obj.addVertex(-100, 0, -100);
    obj.makeTriangle();

    return obj.toString();
}

