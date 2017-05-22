#include "Model_3D.h"

Model_3D::Model_3D(){
    ;
}
Model_3D::Model_3D(std::string path){
    model_path = path;
}

void Model_3D::load(){
    std::ifstream ifile(model_path);
    std::string line;

    while (std::getline(ifile, line)) {

        std::istringstream buffer(line);
        std::vector<std::string> lineVector {  std::istream_iterator<std::string>(buffer), 
                                               std::istream_iterator<std::string>()
        };

        points.push_back(stof(lineVector[0]));
        points.push_back(stof(lineVector[1]));
        points.push_back(stof(lineVector[2]));
    }
}


std::vector<float> Model_3D::getPoints(){
    return points;
}

std::string Model_3D::toString(){
    return "";
}

