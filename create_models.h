#include <stdlib.h>

#define NV_BOX 10
#define NV_PLANE 10

float* create_plane();
float* create_box(float X, float Y, float Z);
float* create_sphere(float radius, int slices, int stacks);
float* create_cone(float bottom_radius, float height, int slices, int stacks);
