#include "create_models.h"


void add_point(FILE* f, float x, float y, float z){
    fprintf(f, "%f %f %f\n", x, y, z);
}

void create_plane(FILE* f){

  add_point(f, 100, 0, 100);
  add_point(f, 100, 0, -100);
  add_point(f, -100, 0, -100);

  add_point(f, 100, 0, 100);
  add_point(f, -100, 0, 100);
  add_point(f, -100, 0, -100);
}

void create_box(FILE* f, float X, float Y, float Z, int divisions){
  float x, y, z, hX, hY, hZ, v1X, v1Y, v1Z, v2X, v2Y, v2Z;

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

        add_point(f, v1X, v2Y, k * hZ);
        add_point(f, v1X, v1Y, k * hZ);
        add_point(f, v2X, v2Y, k * hZ);

        add_point(f, v2X, v1Y, k * hZ);
        add_point(f, v2X, v2Y, k * hZ);
        add_point(f, v1X, v1Y, k * hZ);
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

        add_point(f, v1X, k * hY, v1Z);
        add_point(f, v2X, k * hY, v2Z);
        add_point(f, v2X, k * hY, v1Z);

        add_point(f, v1X, k * hY, v2Z);
        add_point(f, v2X, k * hY, v2Z);
        add_point(f, v1X, k * hY, v1Z);
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

        add_point(f, k * hX, v2Y, v1Z);
        add_point(f, k * hX, v1Y, v1Z);
        add_point(f, k * hX, v2Y, v2Z);

        add_point(f, k * hX, v1Y, v2Z);
        add_point(f, k * hX, v2Y, v2Z);
        add_point(f, k * hX, v1Y, v1Z);
      }
    }
  }
}

void create_sphere(FILE* f, float radius, int slices, int stacks){

  float sliceAngle = M_PI / slices;

  float alpha;
  float beta;
  float v1X, v1Y, v1Z, v2X, v2Y, v2Z;

  float fa = 1;
  float fb = 1;
  float fc = 1;

  int i, j;
  for (i = 0; i < stacks; i++) {
    for(j = 0; j < slices; j++) {
      alpha = j * 2*sliceAngle;
      beta = -M_PI/2 + i * sliceAngle;

      v1X = fa * radius * sin(alpha + 2*sliceAngle) * cos(beta);
      v1Y = fb * radius * sin(beta);
      v1Z = fc * radius * cos(alpha + 2*sliceAngle) * cos(beta);

      v2X = fa * radius * sin(alpha) * cos(beta + sliceAngle);
      v2Y = fb * radius * sin(beta + sliceAngle);
      v2Z = fc * radius * cos(alpha) * cos(beta + sliceAngle);


      add_point(f,
                          fa * radius * sin(alpha) * cos(beta),
                          fb * radius * sin(beta),
                          fc * radius * cos(alpha) * cos(beta));
      add_point(f, v1X, v1Y, v1Z);
      add_point(f, v2X, v2Y, v2Z);

      add_point(f,
                          fa * radius * sin(alpha + 2*sliceAngle) * cos(beta + sliceAngle),
                          fb * radius * sin(beta + sliceAngle),
                          fc * radius * cos(alpha + 2*sliceAngle) * cos(beta + sliceAngle));
      add_point(f, v2X, v2Y, v2Z);
      add_point(f, v1X, v1Y, v1Z);
    }
  }
}

/*
int create_sphere(FILE* f, float radius, int slices, int stacks){
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


      nPoints = add_point(f,
                          radius * sin(alpha) * cos(beta),
                          radius * sin(beta),
                          radius * cos(alpha) * cos(beta));
      nPoints = add_point(f, v1X, v1Y, v1Z);
      nPoints = add_point(f, v2X, v2Y, v2Z);

      nPoints = add_point(f,
                          radius * sin(alpha + 2*sliceAngle) * cos(beta + sliceAngle),
                          radius * sin(beta + sliceAngle),
                          radius * cos(alpha + 2*sliceAngle) * cos(beta + sliceAngle));
      nPoints = add_point(f, v2X, v2Y, v2Z);
      nPoints = add_point(f, v1X, v1Y, v1Z);
    }
  }

}
*/


void create_cone(FILE* f, float radius, float height, int slices, int stacks){

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

    add_point(f, v1X, height, v1Z);
    add_point(f, 0, height, 0);
    add_point(f, v2X, height, v2Z);
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

      add_point(f, radius  * v1X, v1Y, radius  * v1Z);
      add_point(f, radius  * v2X, v1Y, radius  * v2Z);
      add_point(f, radius2 * v1X, v2Y, radius2 * v1Z);

      add_point(f, radius  * v2X, v1Y, radius  * v2Z);
      add_point(f, radius2 * v2X, v2Y, radius2 * v2Z);
      add_point(f, radius2 * v1X, v2Y, radius2 * v1Z);
    }

    radius = radius - radiusDiff;
    height = height + stackHeight;
  }
}

