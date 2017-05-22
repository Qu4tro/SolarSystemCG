#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <iterator>
#include <tuple>
#include <math.h>

#include "fTriple.h"

#define RADIAN_UNIT (M_PI / 360)
#define UP_GLUT 101
#define DOWN_GLUT 103


struct Camera {
    virtual void move() = 0;
    virtual ~Camera() { }

    virtual fTriple position() = 0;
    virtual fTriple focus() = 0;
    virtual fTriple tilt() = 0;

    virtual void specialkey(int key, bool pressed) = 0;
    virtual void normalkey(unsigned char key, bool pressed) = 0;
};
