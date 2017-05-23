#include "Model_stl.h"

Model_stl::Model_stl(){
    ;
}
Model_stl::Model_stl(std::string path){
    model_path = path;
}

void Model_stl::load(){
    std::ifstream ifile(model_path);
    std::string line;

    while (std::getline(ifile, line)) {
        if (line.find("vertex") != std::string::npos) {

            std::istringstream buffer(line);
            std::vector<std::string> lineVector {  std::istream_iterator<std::string>(buffer), 
                                                   std::istream_iterator<std::string>()
            };

            points.push_back(stof(lineVector[1]));
            points.push_back(stof(lineVector[2]));
            points.push_back(stof(lineVector[3]));
        }
    }
}


std::vector<float> Model_stl::getPoints(){
    return points;
}

std::string Model_stl::toString(){
    return "";
}

