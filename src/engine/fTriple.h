#ifndef TRIPLE_H
#define TRIPLE_H

#include <iostream>
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
    
};


#endif
