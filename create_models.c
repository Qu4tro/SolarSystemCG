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
    int nPoints = 0;
    int nVertices;

    float alpha;
    float beta;
    
    int i, j, loops = 0;
	for (i = 0; i < stacks; i++) {
		for(j = 0; j < slices; j++) {
            loops++;
			alpha = j * (2 * M_PI) / slices;
			beta = -M_PI/2 + i * M_PI / slices;
            nPoints = add_point(vertices, nPoints,
                radius * sin(alpha) * cos(beta), radius * sin(beta), radius  * cos(alpha) * cos(beta));
            nPoints = add_point(vertices, nPoints,
                radius * sin(alpha + 2 * M_PI / slices) * cos(beta), radius * sin(beta), radius * cos(alpha + 2 * M_PI / slices) * cos(beta));
            nPoints = add_point(vertices, nPoints,
                radius * sin(alpha) * cos(beta + M_PI / slices), radius * sin(beta + M_PI/ slices), radius * cos(alpha) * cos(beta + M_PI / slices));

            nPoints = add_point(vertices, nPoints,
                radius * sin(alpha + 2 * M_PI / slices)*cos(beta + M_PI / slices), 
                radius * sin(beta + M_PI / slices), 
                radius * cos(alpha + 2 * M_PI / slices) * cos(beta + M_PI / slices));
            nPoints = add_point(vertices, nPoints,
                radius * sin(alpha) * cos(beta + M_PI / slices), radius * sin(beta + M_PI / slices), radius * cos(alpha) * cos(beta + M_PI / slices));
            nPoints = add_point(vertices, nPoints,
                radius * sin(alpha + 2 * M_PI / slices) * cos(beta), radius * sin(beta), radius * cos(alpha + 2 * M_PI / slices) * cos(beta));
		}
	}

    nVertices = (6 * loops);
    return nVertices;


}


int create_cone(float* vertices, float radius, float height, int slices, int stacks){

    int nPoints = 0;
    int nVertices;

    float alpha;
    float beta;

    stacks += 1;

    int i;
	for (i = 0; i < slices; i++) {
		alpha = i * (2 * M_PI) / slices;
		beta = (i + 1) * (2 * M_PI) / slices;

        nPoints = add_point(vertices, nPoints, 
            0.0f, -height / 2, 0.0f);
        nPoints = add_point(vertices, nPoints,
            radius * (sin(beta)), -height / 2, radius * cos(beta));
        nPoints = add_point(vertices, nPoints,
            radius *(sin(alpha)), -height / 2, radius * cos(alpha));

        nPoints = add_point(vertices, nPoints, 
		    0, height / 2, 0);
        nPoints = add_point(vertices, nPoints, 
		    radius * (sin(alpha)), -height / 2, radius * cos(alpha));
        nPoints = add_point(vertices, nPoints, 
            radius * (sin(beta)), -height / 2, radius * cos(beta));
    }
	
    nVertices = (6 * (i - 1));
    return nVertices;
}
