#include <stdlib.h>

#define NV_BOX 10
#define NV_PLANE 10

int create_plane(float* vertices);
int create_box(float* vertices, float X, float Y, float Z);
int create_sphere(float* vertices, float radius, int slices, int stacks);
int create_cone(float* vertices, float bottom_radius, float height, int slices, int stacks);
