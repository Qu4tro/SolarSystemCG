#include "OrbitalCamera.h"

OrbitalCamera::OrbitalCamera() {
    std::fill_n(specialKeys, 127, false);
    std::fill_n(normalKeys,  255, false);
    cameraSpeed     = 2.5;
    cameraPosition  = std::make_tuple(50, 1, 0);
    cameraFocus     = std::make_tuple(0, 0, 0);
    cameraTilt      = std::make_tuple(0, 1, 0);
}

OrbitalCamera::~OrbitalCamera() { };

void OrbitalCamera::specialkey(int key, bool pressed){
    specialKeys[key] = pressed;
}
void OrbitalCamera::normalkey(int key, bool pressed){
    normalKeys[key] = pressed;
}


std::tuple<float, float, float> OrbitalCamera::position(){
    return sphericToCartesian(cameraPosition, cameraFocus);
}

std::tuple<float, float, float> OrbitalCamera::focus(){
    return cameraFocus;
}

std::tuple<float, float, float> OrbitalCamera::tilt(){
    return cameraTilt;
}

void OrbitalCamera::move(){
    if (normalKeys['w']){
        std::get<1>(cameraPosition) -= cameraSpeed * RADIAN_UNIT;
        if (std::get<1>(cameraPosition) <= 0){
            std::get<1>(cameraPosition) = RADIAN_UNIT;
        }
    }
    if (normalKeys['s']){
        std::get<1>(cameraPosition) += cameraSpeed * RADIAN_UNIT;
        if (std::get<1>(cameraPosition) >= M_PI) {
            std::get<1>(cameraPosition) = M_PI - RADIAN_UNIT;
        }
    }
    if (specialKeys[UP_GLUT]){
        std::get<0>(cameraPosition) -= cameraSpeed * 0.1;
        if (std::get<0>(cameraPosition) < 0) {
            std::get<0>(cameraPosition) = 0.1;
        }
    }
    if (specialKeys[DOWN_GLUT]){
        std::get<0>(cameraPosition) += cameraSpeed * 0.1;
    }
    if (normalKeys['a']){
        std::get<2>(cameraPosition) += cameraSpeed * RADIAN_UNIT;
    }
    if (normalKeys['d']){
        std::get<2>(cameraPosition) -= cameraSpeed * RADIAN_UNIT;
    }
}

