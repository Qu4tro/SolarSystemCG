#pragma once

#include <vector>
#include <string>

struct Model {

    std::string model_path;

    virtual void load() = 0;

    virtual std::vector<float> getVertices() = 0;
    virtual std::vector<float> getNormals() = 0;
    virtual std::vector<float> getTexcoords() = 0;
    virtual bool loaded() = 0;
    virtual std::string getPath() = 0;

    virtual std::string toString() = 0;
    virtual ~Model() { }
};


