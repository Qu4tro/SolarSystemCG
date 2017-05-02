#include "fTriple.h"

fTriple::fTriple(){
    x = 0;
    y = 0;
    z = 0;
}

fTriple::fTriple(const fTriple &t){
    x = t.x;
    y = t.y;
    z = t.z;
}

fTriple::fTriple(float X, float Y, float Z){
    x = X;
    y = Y;
    z = Z;
}

void fTriple::incr(fTriple t1){
    x = x + t1.x;
    y = y + t1.y;
    z = z + t1.z;
}


void fTriple::vector_scale(float k){
    x *= k;
    y *= k;
    z *= k;
}

void fTriple::vector_cross(fTriple t1){
    x = y * t1.z - z * t1.y;
    y = z * t1.x - x * t1.z;
    z = x * t1.y - y * t1.x;
}

void fTriple::vector_normalize(){
    float len = sqrt(x*x + y*y + z*z);
     
    if(len <= 0.0001){
        x = 0;
        y = 0;
        z = 0;
        return;
    }
    x /= len;
    y /= len;
    z /= len;
}

void fTriple::sphericToCartesian(fTriple center){
    float rad = x;
    float lat = y;
    float lon = z;

    x = rad * sin(lat) * cos(lon) - center.x;
    z = rad * sin(lat) * sin(lon) - center.y;
    y = rad * cos(lat)            - center.z;
}

void fTriple::cartesianToSpheric(fTriple center){
    float X2 = x - center.x;
    float Y2 = y - center.y;
    float Z2 = z - center.z;

    x = sqrt(pow(X2, 2) + pow(Y2, 2) + pow(Z2, 2));
    y = atan(Z2 / X2);
    z = acos(Y2 / x);
}

void fTriple::print(){
    std::cout << "(" << x << " " << y << " " << z << ")" << std::endl;
}


std::string fTriple::toString(){
    std::ostringstream stringStream;
    stringStream << "(";
    stringStream << x << " ";
    stringStream << y << " ";
    stringStream << z;
    stringStream << ")" << std::endl;

    return stringStream.str();
}
