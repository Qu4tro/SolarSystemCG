#pragma once

#include <vector>
#include <string>

#include <iterator>
#include <fstream>
#include <sstream>

#include "Model.h"

struct Model_3D : Model {

    std::string model_path;
    std::vector<float> points;

    Model_3D();
    Model_3D(std::string);
    void load();

    std::vector<float> getPoints();

    std::string toString();
};
