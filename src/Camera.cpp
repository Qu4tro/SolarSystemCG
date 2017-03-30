#include "Camera.h"

std::tuple<float, float, float> sphericToCartesian(std::tuple<float, float, float> coordinates, std::tuple<float, float, float> center){
    float rad = std::get<0>(coordinates);
    float lat = std::get<1>(coordinates);
    float lon = std::get<2>(coordinates);

    float X = rad * sin(lat) * cos(lon) - std::get<0>(center);
    float Z = rad * sin(lat) * sin(lon) - std::get<1>(center);
    float Y = rad * cos(lat)            - std::get<2>(center);

    return std::make_tuple(X, Y, Z);
}

std::tuple<float, float, float> cartesianToSpheric(std::tuple<float, float, float> coordinates, std::tuple<float, float, float> center){
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


