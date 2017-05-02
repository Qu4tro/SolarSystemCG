#include "Cone.h"

Cone::Cone(){
    radius = 1;
    height = 2;
    slices = 44;
    stacks = 44;
}

Cone::Cone(float radius_, float height_){
    radius = radius_;
    height = height_;
    slices = 44;
    stacks = 44;
}

Cone::Cone(float radius_, float height_, float slices_, float stacks_){
    radius = radius_;
    height = height_;
    slices = slices_;
    stacks = stacks_;
}

std::vector<fTriple> Cone::getPoints(){

    std::vector<fTriple> points;

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

        points.push_back(fTriple(v1X, height, v1Z));
        points.push_back(fTriple(0, height, 0));
        points.push_back(fTriple(v2X, height, v2Z));
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

            points.push_back(fTriple(radius  * v1X, v1Y, radius  * v1Z));
            points.push_back(fTriple(radius  * v2X, v1Y, radius  * v2Z));
            points.push_back(fTriple(radius2 * v1X, v2Y, radius2 * v1Z));

            points.push_back(fTriple(radius  * v2X, v1Y, radius  * v2Z));
            points.push_back(fTriple(radius2 * v2X, v2Y, radius2 * v2Z));
            points.push_back(fTriple(radius2 * v1X, v2Y, radius2 * v1Z));
        }

        radius = radius - radiusDiff;
        height = height + stackHeight;
    }

    return points;
}

