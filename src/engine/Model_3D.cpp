#include "Model_3D.h"

#include <iostream>

Model_3D::Model_3D(){
    loaded = false;
}
Model_3D::Model_3D(std::string path){
    loaded = false;
    model_path = path;
}

void Model_3D::load(){
    /* assert(loaded == false); */
    std::ifstream ifile(model_path);
    std::string line;

    while (std::getline(ifile, line)) {

        std::istringstream buffer(line);
        std::vector<std::string> lineVector {  std::istream_iterator<std::string>(buffer), 
                                               std::istream_iterator<std::string>()
        };

        if (lineVector[0] == "v"){
            vertices.push_back(stof(lineVector[1]));
            vertices.push_back(stof(lineVector[2]));
            vertices.push_back(stof(lineVector[3]));
        } else if (lineVector[0] == "vn"){
            normals.push_back(stof(lineVector[1]));
            normals.push_back(stof(lineVector[2]));
            normals.push_back(stof(lineVector[3]));
        } else if (lineVector[0] == "vt"){
            texcoords.push_back(stof(lineVector[1]));
            texcoords.push_back(stof(lineVector[2]));
        } else {
            ; 
        }
    }

    std::cout << toString() << std::endl;
    loaded = true;
}

std::vector<float> Model_3D::getVertices(){
    return vertices;
}
std::vector<float> Model_3D::getNormals(){
    return normals;
}
std::vector<float> Model_3D::getTexcoords(){
    return texcoords;
}
std::string Model_3D::toString(){
    std::ostringstream stringStream;
    stringStream << "Model: ";
    stringStream << "path=" << model_path << " ";
    stringStream << "loaded=" << loaded << " ";
    stringStream << "#V=" << vertices.size() << " ";
    stringStream << "#VN=" << normals.size() << " ";
    stringStream << "#VT=" << texcoords.size() << " ";
    stringStream << std::endl;

    return stringStream.str();
}

