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

  return nPoints / 3;
}

int create_box(float* vertices, float X, float Y, float Z, int divisions){
  //TODO divisions

  float x, y, z, hX, hY, hZ, v1X, v1Y, v1Z, v2X, v2Y, v2Z;
  int nPoints = 0;

  x = X / divisions;
  y = Y / divisions;
  z = Z / divisions;
  hX = X / 2;
  hY = Y / 2;
  hZ = Z / 2;

  // front and back-face
  for(int k = -1; k < 2; k += 2){
    for(int i = 0; i < divisions; i++){
      for(int j = 0; j < divisions; j++){

        v1X = hX - x * i;
        v1Y = hY - y * j;

        v2X = hX - x * (i + 1);
        v2Y = hY - y * (j + 1);

        nPoints = add_point(vertices, nPoints, v1X, v2Y, k * hZ);
        nPoints = add_point(vertices, nPoints, v1X, v1Y, k * hZ);
        nPoints = add_point(vertices, nPoints, v2X, v2Y, k * hZ);

        nPoints = add_point(vertices, nPoints, v2X, v1Y, k * hZ);
        nPoints = add_point(vertices, nPoints, v2X, v2Y, k * hZ);
        nPoints = add_point(vertices, nPoints, v1X, v1Y, k * hZ);
      }
    }
  }

  // top and bottom-face
  for(int k = -1; k < 2; k += 2){
    for(int i = 0; i < divisions; i++){
      for(int j = 0; j < divisions; j++){

        v1X = hX - x * i;
        v1Z = hZ - z * j;

        v2X = hX - x * (i + 1);
        v2Z = hZ - z * (j + 1);

        nPoints = add_point(vertices, nPoints, v1X, k * hY, v1Z);
        nPoints = add_point(vertices, nPoints, v2X, k * hY, v2Z);
        nPoints = add_point(vertices, nPoints, v2X, k * hY, v1Z);

        nPoints = add_point(vertices, nPoints, v1X, k * hY, v2Z);
        nPoints = add_point(vertices, nPoints, v2X, k * hY, v2Z);
        nPoints = add_point(vertices, nPoints, v1X, k * hY, v1Z);
      }
    }
  }


  // left and right-face
  for(int k = -1; k < 2; k += 2){
    for(int i = 0; i < divisions; i++){
      for(int j = 0; j < divisions; j++){

        v1Y = hY - y * i;
        v1Z = hZ - z * j;

        v2Y = hY - y * (i + 1);
        v2Z = hZ - z * (j + 1);

        nPoints = add_point(vertices, nPoints, k * hX, v2Y, v1Z);
        nPoints = add_point(vertices, nPoints, k * hX, v1Y, v1Z);
        nPoints = add_point(vertices, nPoints, k * hX, v2Y, v2Z);

        nPoints = add_point(vertices, nPoints, k * hX, v1Y, v2Z);
        nPoints = add_point(vertices, nPoints, k * hX, v2Y, v2Z);
        nPoints = add_point(vertices, nPoints, k * hX, v1Y, v1Z);
      }
    }
  }

  return nPoints / 3;
}


int create_sphere(float* vertices, float radius, int slices, int stacks){
  int nPoints = 0;

  float sliceAngle = M_PI / slices;

  float alpha;
  float beta;
  float v1X, v1Y, v1Z, v2X, v2Y, v2Z;

  int i, j;
  for (i = 0; i < stacks; i++) {
    for(j = 0; j < slices; j++) {
      alpha = j * 2*sliceAngle;
      beta = -M_PI/2 + i * sliceAngle;

      v1X = radius * sin(alpha + 2*sliceAngle) * cos(beta);
      v1Y = radius * sin(beta);
      v1Z = radius * cos(alpha + 2*sliceAngle) * cos(beta);

      v2X = radius * sin(alpha) * cos(beta + sliceAngle);
      v2Y = radius * sin(beta + sliceAngle);
      v2Z = radius * cos(alpha) * cos(beta + sliceAngle);


      nPoints = add_point(vertices, nPoints,
                          radius * sin(alpha) * cos(beta),
                          radius * sin(beta),
                          radius * cos(alpha) * cos(beta));
      nPoints = add_point(vertices, nPoints, v1X, v1Y, v1Z);
      nPoints = add_point(vertices, nPoints, v2X, v2Y, v2Z);

      nPoints = add_point(vertices, nPoints,
                          radius * sin(alpha + 2*sliceAngle) * cos(beta + sliceAngle),
                          radius * sin(beta + sliceAngle),
                          radius * cos(alpha + 2*sliceAngle) * cos(beta + sliceAngle));
      nPoints = add_point(vertices, nPoints, v2X, v2Y, v2Z);
      nPoints = add_point(vertices, nPoints, v1X, v1Y, v1Z);
    }
  }

  return nPoints / 3;
}


int create_cone(float* vertices, float radius, float height, int slices, int stacks){

  int nPoints = 0;

  float radius2;
  float stackHeight = height / stacks;
  float sliceAngle = 2*M_PI / slices;
  float radiusDiff = radius / stacks;
  float alpha = 0;

  float v1X, v1Y, v1Z, v2X, v2Y, v2Z;

  height = -height / 2;
  for(int j = 0; j < slices; j++) {
    alpha += sliceAngle;
    v1X = radius * sin(alpha);
    v1Y = height;
    v1Z = radius * cos(alpha);

    v2X = radius * sin(alpha + sliceAngle);
    v2Y = height + stackHeight;
    v2Z = radius * cos(alpha + sliceAngle);

    nPoints = add_point(vertices, nPoints, v1X, height, v1Z);
    nPoints = add_point(vertices, nPoints, 0, height, 0);
    nPoints = add_point(vertices, nPoints, v2X, height, v2Z);
  }

  for (int i = 0; i < stacks; i++) {
    for(int j = 0; j < slices; j++) {

      alpha += sliceAngle;
      radius2 = radius - radiusDiff;
      v1X = sin(alpha);
      v1Y = height;
      v1Z = cos(alpha);

      v2X = sin(alpha + sliceAngle);
      v2Y = height + stackHeight;
      v2Z = cos(alpha + sliceAngle);

      nPoints = add_point(vertices, nPoints, radius  * v1X, v1Y, radius  * v1Z);
      nPoints = add_point(vertices, nPoints, radius  * v2X, v1Y, radius  * v2Z);
      nPoints = add_point(vertices, nPoints, radius2 * v1X, v2Y, radius2 * v1Z);

      nPoints = add_point(vertices, nPoints, radius  * v2X, v1Y, radius  * v2Z);
      nPoints = add_point(vertices, nPoints, radius2 * v2X, v2Y, radius2 * v2Z);
      nPoints = add_point(vertices, nPoints, radius2 * v1X, v2Y, radius2 * v1Z);
    }

    radius = radius - radiusDiff;
    height = height + stackHeight;
  }

  return nPoints / 3;
}

