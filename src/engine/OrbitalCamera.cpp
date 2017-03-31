#include "OrbitalCamera.h"

OrbitalCamera::OrbitalCamera() {
    std::fill_n(specialKeys, 128, false);
    std::fill_n(normalKeys,  256, false);
    cameraSpeed     = 2.5;
    cameraPosition  = fTriple(30.0f, 1.0f, 0.0f);
    cameraFocus     = fTriple(0.0f, 0.0f, 0.0f);
    cameraTilt      = fTriple(0.0f, 1.0f, 0.0f);
}

OrbitalCamera::~OrbitalCamera() { };

void OrbitalCamera::specialkey(int key, bool pressed){
    specialKeys[key] = pressed;
}
void OrbitalCamera::normalkey(unsigned char key, bool pressed){
    normalKeys[key] = pressed;
}

fTriple OrbitalCamera::position(){
    fTriple t = fTriple(cameraPosition);
    t.sphericToCartesian(cameraFocus);
    return t;
}

fTriple OrbitalCamera::focus(){
    return cameraFocus;
}

fTriple OrbitalCamera::tilt(){
    return cameraTilt;
}

void OrbitalCamera::move(){
    if (specialKeys[UP_GLUT]){
        cameraPosition.x -= cameraSpeed * 0.1;
        if (cameraPosition.x < 0) {
            cameraPosition.x = 0.1;
        }
    }
    if (specialKeys[DOWN_GLUT]){
        cameraPosition.x += cameraSpeed * 0.1;
    }

    if (normalKeys['w']){
        cameraPosition.y -= cameraSpeed * RADIAN_UNIT;
        if (cameraPosition.y <= 0){
            cameraPosition.y = RADIAN_UNIT;
        }
    }
    if (normalKeys['s']){
        cameraPosition.y += cameraSpeed * RADIAN_UNIT;
        if (cameraPosition.y >= M_PI) {
            cameraPosition.y = M_PI - RADIAN_UNIT;
        }
    }
    if (normalKeys['a']){
        cameraPosition.z += cameraSpeed * RADIAN_UNIT;
    }
    if (normalKeys['d']){
        cameraPosition.z -= cameraSpeed * RADIAN_UNIT;
    }
}
