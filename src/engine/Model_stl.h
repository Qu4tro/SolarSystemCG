#pragma once

#include <vector>
#include <string>

#include <iterator>
#include <fstream>
#include <sstream>

#include "Model.h"

struct Model_stl : Model {

    std::string model_path;
    std::vector<float> points;

    Model_stl();
    Model_stl(std::string);
    void load();

    std::vector<float> getPoints();

    std::string toString();
};
