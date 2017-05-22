#pragma once

#include <vector>
#include <string>

struct Model {

    std::string model_path;

    virtual void load() = 0;

    virtual std::vector<float> getPoints() = 0;

    virtual std::string toString() = 0;
    virtual ~Model() { }
};

