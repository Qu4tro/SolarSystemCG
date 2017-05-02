#include "Sphere.h"

Sphere::Sphere(){
    radius = 1;
    slices = 44;
    stacks = 44;
}

Sphere::Sphere(float radius_){
    radius = radius_;
    slices = 44;
    stacks = 44;
}

Sphere::Sphere(float radius_, float slices_, float stacks_){
    radius = radius_;
    slices = slices_;
    stacks = stacks_;
}

std::vector<fTriple> Sphere::getPoints(){

    std::vector<fTriple> points;

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


            points.push_back(fTriple(
                    radius * sin(alpha) * cos(beta),
                    radius * sin(beta),
                    radius * cos(alpha) * cos(beta)));
            points.push_back(fTriple(v1X, v1Y, v1Z));
            points.push_back(fTriple(v2X, v2Y, v2Z));

            points.push_back(fTriple(
                    radius * sin(alpha + 2*sliceAngle) * cos(beta + sliceAngle),
                    radius * sin(beta + sliceAngle),
                    radius * cos(alpha + 2*sliceAngle) * cos(beta + sliceAngle)));
            points.push_back(fTriple(v2X, v2Y, v2Z));
            points.push_back(fTriple(v1X, v1Y, v1Z));
        }
    }

    return points;
}

