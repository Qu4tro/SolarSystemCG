#pragma once

#include <string>

#include <iostream>
#include <sstream>
#include <math.h>

struct fTriple {
    fTriple();
    fTriple(float X, float Y, float Z);
    fTriple(const fTriple &t);

    float x;
    float y;
    float z;

    void incr(fTriple t1);
    void print();

    void vector_normalize();
    void vector_cross(fTriple t1);
    void vector_dotproduct(fTriple t1);
    void vector_scale(float k);
    void sphericToCartesian(fTriple center);
    void cartesianToSpheric(fTriple center);
    
    std::string toString();
};


