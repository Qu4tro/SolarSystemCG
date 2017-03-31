#include "fTriple.h"

fTriple::fTriple(){
    fst = x = 0;
    snd = y = 0;
    trd = z = 0;
}

fTriple::fTriple(const fTriple &t){
    fst = x = t.x;
    snd = y = t.y;
    trd = z = t.z;
}

fTriple::fTriple(float X, float Y, float Z){
    fst = x = X;
    snd = y = Y;
    trd = z = Z;
}

void fTriple::incr(fTriple t1){
    fst = x = x + t1.x;
    snd = y = y + t1.y;
    trd = z = z + t1.z;
}


void fTriple::vector_scale(float k){
    x *= k;
    y *= k;
    z *= k;
}

void fTriple::vector_cross(fTriple t1){
    fst = x = y * t1.z - z * t1.y;
    snd = y = z * t1.x - x * t1.z;
    trd = z = x * t1.y - y * t1.x;
}

void fTriple::vector_normalize(){
    float len = sqrt(x*x + y*y + z*z);
     
    if(len == 0){
        x = 0;
        y = 0;
        z = 0;
        return;
    }
    x /= len;
    y /= len;
    z /= len;
}

fTriple sphericToCartesian(fTriple coordinates, fTriple center){
    float rad = coordinates.fst;
    float lat = coordinates.snd;
    float lon = coordinates.trd;

    float X = rad * sin(lat) * cos(lon) - center.x;
    float Z = rad * sin(lat) * sin(lon) - center.y;
    float Y = rad * cos(lat)            - center.z;

    return fTriple(X, Y, Z);
}

fTriple cartesianToSpheric(fTriple coordinates, fTriple center){
    float X2 = coordinates.x - center.x;
    float Y2 = coordinates.y - center.y;
    float Z2 = coordinates.z - center.z;

    float rad   = sqrt(pow(X2, 2) + pow(Y2, 2) + pow(Z2, 2));
    float lon   = atan(Z2 / X2);
    float lat   = acos(Y2 / rad);

    return fTriple(rad, lat, lon);
}

void fTriple::print(){
    std::cout << "(" << x << " " << y << " " << z << ")";
    fflush(stdout);
}


