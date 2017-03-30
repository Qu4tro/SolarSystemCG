#ifndef CAMERA_H
#define CAMERA_H

#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <iterator>
#include <tuple>
#include <math.h>


std::tuple<float, float, float> cartesianToSpheric(std::tuple<float, float, float> coordinates, std::tuple<float, float, float> center);
std::tuple<float, float, float> sphericToCartesian(std::tuple<float, float, float> coordinates, std::tuple<float, float, float> center);

struct Camera {
    virtual void move() = 0;
    virtual ~Camera() { }

    virtual std::tuple<float, float, float> position() = 0;
    virtual std::tuple<float, float, float> focus() = 0;
    virtual std::tuple<float, float, float> tilt() = 0;

    virtual void specialkey(int key, bool pressed) = 0;
    virtual void normalkey(int key, bool pressed) = 0;
};

#endif
