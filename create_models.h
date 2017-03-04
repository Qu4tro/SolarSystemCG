#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define NV_BOX 10
#define NV_PLANE 10

void create_plane(FILE* f);
void create_box(FILE* f, float X, float Y, float Z, int divisions);
void create_sphere(FILE* f, float radius, int slices, int stacks);
void create_cone(FILE* f, float radius, float height, int slices, int stacks);
