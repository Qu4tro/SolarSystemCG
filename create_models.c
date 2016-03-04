#include "create_models.h"

void add_point(float* vertices, float x, float y, float z){
    int len = vertices[0];
    vertices[len] = x; 
    vertices[len + 1] = y; 
    vertices[len + 2] = z; 
    
    vertices[0] += 3;
}

void add_square(float* vertices,
                float xA, float yA, float zA,
                float xB, float yB, float zB,
                float xC, float yC, float zC){
/*
    A         B
    ///////////
    //       //
    //       //
    //       //
    //       //
    ///////////
    C         D
*/

    float xD, yD, zD;

    /* xD = */ 

    add_point(vertices, xA, yA, zA);
    add_point(vertices, xB, yB, zB);
    add_point(vertices, xC, yC, zC);

    add_point(vertices, xA, yA, zA);
    add_point(vertices, xD, yD, zD);
    add_point(vertices, xB, yB, zB);

}

float* create_plane(){

    float* vertices = malloc(NV_PLANE * sizeof(float));

    add_point(vertices, 100, 0, 100);
    add_point(vertices, 100, 0, -100);
    add_point(vertices, -100, 0, -100);

    add_point(vertices, 100, 0, 100);
    add_point(vertices, -100, 0, 100);
    add_point(vertices, -100, 0, -100);

    return vertices;
}

float* create_box(float X, float Y, float Z){

    float* vertices = malloc(NV_BOX * sizeof(float));

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

    return vertices;
}


float* create_sphere(float radius, int slices, int stacks){
    return NULL;
}
float* create_cone(float bottom_radius, float height, int slices, int stacks){
    return NULL;
}
