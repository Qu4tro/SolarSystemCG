#pragma once

#include <assert.h>
#include <vector>
#include <string>

#include <iterator>
#include <fstream>
#include <sstream>

#include "Model.h"

class Model_3D : public Model {

    private:
        std::vector<float> vertices;
        std::vector<float> normals;
        std::vector<float> texcoords;
        std::string model_path;
        bool first_run;


    public:
        Model_3D();
        Model_3D(std::string);

        void load();
        bool loaded();
        std::string getPath();

        std::vector<float> getVertices();
        std::vector<float> getNormals();
        std::vector<float> getTexcoords();

        std::string toString();
};
