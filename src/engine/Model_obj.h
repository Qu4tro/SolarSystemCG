#pragma once

#include <vector>
#include <string>

#include "fTriple.h"
#include "Model.h"

struct Model_obj : Model {

    std::string model_path;
    std::vector<float> points;

    Model_obj(std::string);
    void load();

    std::vector<float> getPoints();

    std::string toString();
};
