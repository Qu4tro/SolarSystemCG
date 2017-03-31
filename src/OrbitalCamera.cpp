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
    return sphericToCartesian(cameraPosition, cameraFocus);
}

fTriple OrbitalCamera::focus(){
    return cameraFocus;
}

fTriple OrbitalCamera::tilt(){
    return cameraTilt;
}

void OrbitalCamera::move(){
    if (specialKeys[UP_GLUT]){
        cameraPosition.fst -= cameraSpeed * 0.1;
        if (cameraPosition.fst < 0) {
            cameraPosition.fst = 0.1;
        }
    }
    if (specialKeys[DOWN_GLUT]){
        cameraPosition.fst += cameraSpeed * 0.1;
    }

    if (normalKeys['w']){
        cameraPosition.snd -= cameraSpeed * RADIAN_UNIT;
        if (cameraPosition.snd <= 0){
            cameraPosition.snd = RADIAN_UNIT;
        }
    }
    if (normalKeys['s']){
        cameraPosition.snd += cameraSpeed * RADIAN_UNIT;
        if (cameraPosition.snd >= M_PI) {
            cameraPosition.snd = M_PI - RADIAN_UNIT;
        }
    }
    if (normalKeys['a']){
        cameraPosition.trd += cameraSpeed * RADIAN_UNIT;
    }
    if (normalKeys['d']){
        cameraPosition.trd -= cameraSpeed * RADIAN_UNIT;
    }
}
