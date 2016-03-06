#include "create_models.h"


int add_point(float* vertices, int n, float x, float y, float z){
    vertices[n] = x; 
    vertices[n + 1] = y; 
    vertices[n + 2] = z; 
    
    return n + 3;
}

int create_plane(float* vertices){

    int nPoints = 0;
    int nVertices = 6;

    nPoints = add_point(vertices, nPoints, 100, 0, 100);
    nPoints = add_point(vertices, nPoints, 100, 0, -100);
    nPoints = add_point(vertices, nPoints, -100, 0, -100);

    nPoints = add_point(vertices, nPoints, 100, 0, 100);
    nPoints = add_point(vertices, nPoints, -100, 0, 100);
    nPoints = add_point(vertices, nPoints, -100, 0, -100);

    return nVertices;
}

int create_box(float* vertices, float X, float Y, float Z){

    int nPoints = 0;
    int nVertices = 36;

    // front-face
    nPoints = add_point(vertices, nPoints,  X,  Y,  Z);
    nPoints = add_point(vertices, nPoints, -X, -Y,  Z);
    nPoints = add_point(vertices, nPoints,  X, -Y,  Z);

    nPoints = add_point(vertices, nPoints,  X,  Y,  Z);
    nPoints = add_point(vertices, nPoints, -X,  Y,  Z);
    nPoints = add_point(vertices, nPoints, -X, -Y,  Z);
    
    // back-face
    nPoints = add_point(vertices, nPoints,  X,  Y, -Z);
    nPoints = add_point(vertices, nPoints,  X, -Y, -Z);
    nPoints = add_point(vertices, nPoints, -X,  Y, -Z);

    nPoints = add_point(vertices, nPoints,  X, -Y, -Z);
    nPoints = add_point(vertices, nPoints, -X, -Y, -Z);
    nPoints = add_point(vertices, nPoints, -X,  Y, -Z);

    // top-face
    nPoints = add_point(vertices, nPoints,  X,  Y,  Z);
    nPoints = add_point(vertices, nPoints, -X,  Y, -Z);
    nPoints = add_point(vertices, nPoints, -X,  Y,  Z);

    nPoints = add_point(vertices, nPoints,  X,  Y,  Z);
    nPoints = add_point(vertices, nPoints,  X,  Y, -Z);
    nPoints = add_point(vertices, nPoints, -X,  Y, -Z);

    // bottom-face
    nPoints = add_point(vertices, nPoints,  X, -Y,  Z);
    nPoints = add_point(vertices, nPoints, -X, -Y,  Z);
    nPoints = add_point(vertices, nPoints, -X, -Y, -Z);

    nPoints = add_point(vertices, nPoints,  X, -Y,  Z);
    nPoints = add_point(vertices, nPoints, -X, -Y, -Z);
    nPoints = add_point(vertices, nPoints,  X, -Y, -Z);

    // left-face
    nPoints = add_point(vertices, nPoints, -X, -Y,  Z);
    nPoints = add_point(vertices, nPoints, -X,  Y,  Z);
    nPoints = add_point(vertices, nPoints, -X, -Y, -Z);

    nPoints = add_point(vertices, nPoints, -X, -Y, -Z);
    nPoints = add_point(vertices, nPoints, -X,  Y,  Z);
    nPoints = add_point(vertices, nPoints, -X,  Y, -Z);

    // right-face
    nPoints = add_point(vertices, nPoints,  X, -Y,  Z);
    nPoints = add_point(vertices, nPoints,  X, -Y, -Z);
    nPoints = add_point(vertices, nPoints,  X,  Y,  Z);

    nPoints = add_point(vertices, nPoints,  X, -Y, -Z);
    nPoints = add_point(vertices, nPoints,  X, -Y,  Z);
    nPoints = add_point(vertices, nPoints,  X,  Y,  Z);

    return nVertices;
}


int create_sphere(float* vertices, float radius, int slices, int stacks){
    return 0;
}


int create_cone(float* vertices, float bottom_radius, float height, int slices, int stacks){

    int nPoints = 0;
    int nVertices = 6;

    nPoints = add_point(vertices, nPoints, 100, 0, 100);
    nPoints = add_point(vertices, nPoints, 100, 0, -100);
    nPoints = add_point(vertices, nPoints, -100, 0, -100);

    nPoints = add_point(vertices, nPoints, 100, 0, 100);
    nPoints = add_point(vertices, nPoints, -100, 0, 100);
    nPoints = add_point(vertices, nPoints, -100, 0, -100);

    return nVertices;

    return 0;
}
