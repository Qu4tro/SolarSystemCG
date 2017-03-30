#ifndef OCAMERA_H
#define OCAMERA_H

#include <vector>
#include <string>
#include <utility>
#include <iterator>
#include <algorithm>
#include <tuple>
#include <math.h>

#include "Camera.h"

#define RADIAN_UNIT (M_PI / 360)
#define UP_GLUT 101
#define DOWN_GLUT 103

class OrbitalCamera : public Camera {

  public:
    OrbitalCamera();
    ~OrbitalCamera();

    void move();

    std::tuple<float, float, float> position();
    std::tuple<float, float, float> focus();
    std::tuple<float, float, float> tilt();

    void specialkey(int key, bool pressed);
    void normalkey(int key, bool pressed);

  private:
    int specialKeys[128];
    char normalKeys[256];
    std::tuple<float, float, float> cameraPosition;
    std::tuple<float, float, float> cameraFocus;
    std::tuple<float, float, float> cameraTilt;
    float cameraSpeed;
};

#endif
