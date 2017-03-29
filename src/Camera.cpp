#include "Camera.h"

Camera::Camera() {
    up = down = fwd = bck = left = right = false;
    cameraSpeed     = 2.5;
    cameraPosition  = std::make_tuple(50, 1, 0);
    cameraFocus     = std::make_tuple(0, 0, 0);
    cameraTilt      = std::make_tuple(0, 1, 0);
}

auto sphericToCartesian(auto coordinates, auto center){
    float rad = std::get<0>(coordinates);
    float lat = std::get<1>(coordinates);
    float lon = std::get<2>(coordinates);

    float X = rad * sin(lat) * cos(lon) - std::get<0>(center);
    float Z = rad * sin(lat) * sin(lon) - std::get<1>(center);
    float Y = rad * cos(lat)            - std::get<2>(center);

    return std::make_tuple(X, Y, Z);
}

auto cartesianToSpheric(auto coordinates, auto center){
    float X = std::get<0>(coordinates);
    float Y = std::get<1>(coordinates);
    float Z = std::get<2>(coordinates);

    float X2 = X - std::get<0>(center);
    float Y2 = Y - std::get<1>(center);
    float Z2 = Z - std::get<2>(center);

    float rad   = sqrt(pow(X2, 2) + pow(Y2, 2) + pow(Z2, 2));
    float lon   = atan(Z2 / X2);
    float lat   = acos(Y2 / rad);

    return std::make_tuple(rad, lat, lon);
}

std::tuple<float, float, float> Camera::cartesianPosition(){
    return sphericToCartesian(cameraPosition, cameraFocus);
}

void Camera::move(){
    if (up){
        std::get<1>(cameraPosition) -= cameraSpeed * RADIAN_UNIT;
        if (std::get<1>(cameraPosition) <= 0){
            std::get<1>(cameraPosition) = RADIAN_UNIT;
        }
    }
    if (down){
        std::get<1>(cameraPosition) += cameraSpeed * RADIAN_UNIT;
        if (std::get<1>(cameraPosition) >= M_PI) {
            std::get<1>(cameraPosition) = M_PI - RADIAN_UNIT;
        }
    }
    if (fwd){
        std::get<0>(cameraPosition) -= cameraSpeed * 0.1;
        if (std::get<0>(cameraPosition) < 0) {
            std::get<0>(cameraPosition) = 0.1;
        }
    }
    if (bck){
        std::get<0>(cameraPosition) += cameraSpeed * 0.1;
    }
    if (left){
        std::get<2>(cameraPosition) += cameraSpeed * RADIAN_UNIT;
    }
    if (right){
        std::get<2>(cameraPosition) -= cameraSpeed * RADIAN_UNIT;
    }
}
