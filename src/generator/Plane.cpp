#include "Plane.h"

Plane::Plane(){

}

std::vector<fTriple> Plane::getPoints(){

    std::vector<fTriple> points;

    points.push_back(fTriple(100, 0, 100));
    points.push_back(fTriple(100, 0, -100));
    points.push_back(fTriple(-100, 0, -100));

    points.push_back(fTriple(100, 0, 100));
    points.push_back(fTriple(-100, 0, 100));
    points.push_back(fTriple(-100, 0, -100));

    return points;
}

