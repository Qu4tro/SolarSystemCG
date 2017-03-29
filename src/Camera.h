#ifndef CAMERA_H
#define CAMERA_H

#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <iterator>
#include <tuple>
#include <math.h>

#define RADIAN_UNIT (M_PI / 360)

class Camera {
  public:
    Camera();

    void move();

    std::tuple<float, float, float> cartesianPosition();

    std::tuple<float, float, float> cameraFocus;
    std::tuple<float, float, float> cameraTilt;

    bool up, down, fwd, bck, left, right;
  private:

    std::tuple<float, float, float> cameraPosition;
    float cameraSpeed;

};

#endif
