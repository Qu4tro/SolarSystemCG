#include "create_models.h"

void add_point(float* vertices, float x, float y, float z){
    int len = vertices[0];
    vertices[len] = x; 
    vertices[len + 1] = y; 
    vertices[len + 2] = z; 
    
    vertices[0] += 3;
}

/*
void add_square(float* vertices,
                float xA, float yA, float zA,
                float xB, float yB, float zB,
                float xC, float yC, float zC){
    A         B
    ///////////
    //       //
    //       //
    //       //
    //       //
    ///////////
    C         D
*/ /*

    float xD, yD, zD;


    add_point(vertices, xA, yA, zA);
    add_point(vertices, xB, yB, zB);
    add_point(vertices, xC, yC, zC);

    add_point(vertices, xA, yA, zA);
    add_point(vertices, xD, yD, zD);
    add_point(vertices, xB, yB, zB);
}
*/

int create_plane(float* vertices){

    int nVertices = 6;

    add_point(vertices, 100, 0, 100);
    add_point(vertices, 100, 0, -100);
    add_point(vertices, -100, 0, -100);

    add_point(vertices, 100, 0, 100);
    add_point(vertices, -100, 0, 100);
    add_point(vertices, -100, 0, -100);

    return nVertices;
    /* return vertices; */
}

int create_box(float* vertices, float X, float Y, float Z){

    int nVertices = 6;

    // front-face
    add_point(vertices,  X,  Y,  Z);
    add_point(vertices, -X, -Y,  Z);
    add_point(vertices,  X, -Y,  Z);

    add_point(vertices,  X,  Y,  Z);
    add_point(vertices, -X,  Y,  Z);
    add_point(vertices, -X, -Y,  Z);
    
    // back-face
    add_point(vertices,  X,  Y, -Z);
    add_point(vertices,  X, -Y, -Z);
    add_point(vertices, -X,  Y, -Z);

    add_point(vertices,  X,  Y, -Z);
    add_point(vertices, -X, -Y, -Z);
    add_point(vertices, -X,  Y, -Z);

    // top-face
    add_point(vertices,  X,  Y,  Z);
    add_point(vertices, -X,  Y, -Z);
    add_point(vertices, -X,  Y,  Z);

    add_point(vertices,  X,  Y,  Z);
    add_point(vertices,  X,  Y, -Z);
    add_point(vertices, -X,  Y, -Z);

    // bottom-face
    add_point(vertices,  X, -Y,  Z);
    add_point(vertices, -X, -Y,  Z);
    add_point(vertices, -X, -Y, -Z);

    add_point(vertices,  X, -Y,  Z);
    add_point(vertices,  X, -Y, -Z);
    add_point(vertices, -X, -Y, -Z);

    // left-face
    add_point(vertices, -X, -Y,  Z);
    add_point(vertices, -X,  Y,  Z);
    add_point(vertices, -X, -Y, -Z);

    add_point(vertices, -X, -Y, -Z);
    add_point(vertices, -X, -Y,  Z);
    add_point(vertices, -X,  Y,  Z);

    // right-face
    add_point(vertices, X, -Y,  Z);
    add_point(vertices, X,  Y,  Z);
    add_point(vertices, X, -Y, -Z);

    add_point(vertices, X, -Y, -Z);
    add_point(vertices, X, -Y,  Z);
    add_point(vertices, X,  Y,  Z);

    return nVertices;
}


int create_sphere(float* vertices, float radius, int slices, int stacks){
    return 0;
}
int create_cone(float* vertices, float bottom_radius, float height, int slices, int stacks){
    return 0;
}
