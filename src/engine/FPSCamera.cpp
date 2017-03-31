#include "FPSCamera.h"

FPSCamera::FPSCamera() {
    std::fill_n(specialKeys, 128, false);
    std::fill_n(normalKeys,  256, false);
    cameraSpeed     = 2.5;
    cameraPosition  = fTriple(3.0f, 0.0f, 3.0f);
    cameraFront     = fTriple(0.0f, 0.0f, -1.0f);
    cameraTilt      = fTriple(0.0f, 1.0f, 0.0f);
}

FPSCamera::~FPSCamera() { };

void FPSCamera::specialkey(int key, bool pressed){
    specialKeys[key] = pressed;
}
void FPSCamera::normalkey(unsigned char key, bool pressed){
    normalKeys[key] = pressed;
}

fTriple FPSCamera::position(){
    return cameraPosition;
}
fTriple FPSCamera::focus(){
    float X = cameraPosition.x + cameraFront.x;
    float Y = cameraPosition.y + cameraFront.y;
    float Z = cameraPosition.z + cameraFront.z;
    return fTriple(X, Y, Z);
}

fTriple FPSCamera::tilt(){
    return cameraTilt;
}

void FPSCamera::move(){
    if (normalKeys['w']){
        fTriple t = fTriple(cameraFront);
        t.vector_scale(cameraSpeed);
        cameraPosition.incr(t);
    }
    if (normalKeys['s']){
        fTriple t = fTriple(cameraFront);
        t.vector_scale(-cameraSpeed);
        cameraPosition.incr(t);
    }
    if (normalKeys['a']){
        fTriple t = fTriple(cameraFront);
        t.vector_cross(cameraTilt);
        t.vector_scale(-cameraSpeed);
        t.vector_normalize();
        cameraPosition.incr(t);
    }
    if (normalKeys['d']){
        fTriple t = fTriple(cameraFront);
        t.vector_cross(cameraTilt);
        t.vector_scale(cameraSpeed);
        t.vector_normalize();
        cameraPosition.incr(t);
    }
}
