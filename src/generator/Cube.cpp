#include "Cube.h"

Cube::Cube(){
    width = 1;
    length = 1;
    height = 1;
    partitions = 1;
}

Cube::Cube(float W, float L, float H){
    width = W;
    length = L;
    height = H;
    partitions = 1;
}

Cube::Cube(float W, float L, float H, int divisions){
    width = W;
    length = L;
    height = H;
    partitions = divisions;
}

std::vector<fTriple> Cube::getPoints(){

    std::vector<fTriple> points;

    float x, y, z, hX, hY, hZ, v1X, v1Y, v1Z, v2X, v2Y, v2Z;

    x = width / partitions;
    y = length / partitions;
    z = height / partitions;
    hX = width / 2;
    hY = length / 2;
    hZ = height / 2;

    // front and back-face
    for(int k = -1; k < 2; k += 2){
        for(int i = 0; i < partitions; i++){
            for(int j = 0; j < partitions; j++){

                v1X = hX - x * i;
                v1Y = hY - y * j;

                v2X = hX - x * (i + 1);
                v2Y = hY - y * (j + 1);

                points.push_back(fTriple(v1X, v2Y, k * hZ));
                points.push_back(fTriple(v1X, v1Y, k * hZ));
                points.push_back(fTriple(v2X, v2Y, k * hZ));

                points.push_back(fTriple(v2X, v1Y, k * hZ));
                points.push_back(fTriple(v2X, v2Y, k * hZ));
                points.push_back(fTriple(v1X, v1Y, k * hZ));
            }
        }
    }

    // top and bottom-face
    for(int k = -1; k < 2; k += 2){
        for(int i = 0; i < partitions; i++){
            for(int j = 0; j < partitions; j++){

                v1X = hX - x * i;
                v1Z = hZ - z * j;

                v2X = hX - x * (i + 1);
                v2Z = hZ - z * (j + 1);

                points.push_back(fTriple(v1X, k * hY, v1Z));
                points.push_back(fTriple(v2X, k * hY, v2Z));
                points.push_back(fTriple(v2X, k * hY, v1Z));

                points.push_back(fTriple(v1X, k * hY, v2Z));
                points.push_back(fTriple(v2X, k * hY, v2Z));
                points.push_back(fTriple(v1X, k * hY, v1Z));
            }
        }
    }


    // left and right-face
    for(int k = -1; k < 2; k += 2){
        for(int i = 0; i < partitions; i++){
            for(int j = 0; j < partitions; j++){

                v1Y = hY - y * i;
                v1Z = hZ - z * j;

                v2Y = hY - y * (i + 1);
                v2Z = hZ - z * (j + 1);

                points.push_back(fTriple(k * hX, v2Y, v1Z));
                points.push_back(fTriple(k * hX, v1Y, v1Z));
                points.push_back(fTriple(k * hX, v2Y, v2Z));

                points.push_back(fTriple(k * hX, v1Y, v2Z));
                points.push_back(fTriple(k * hX, v2Y, v2Z));
                points.push_back(fTriple(k * hX, v1Y, v1Z));
            }
        }
    }



    return points;
}

