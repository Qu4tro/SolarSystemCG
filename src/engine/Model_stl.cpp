#include "Model_stl.h"

std::vector<std::string> split(std::string const &input) { 
    std::istringstream buffer(input);
    std::vector<std::string> ret {  std::istream_iterator<std::string>(buffer), 
                                    std::istream_iterator<std::string>()
                                 };
    return ret;
}


Model_stl::Model_stl(){
    ;
}
Model_stl::Model_stl(std::string path){
    model_path = path;
}

void Model_stl::load(){
    std::ifstream ifile(model_path);
    std::string line;
    std::vector<std::string> lineVector;

    while (std::getline(ifile, line)) {
        if (line.find("vertex") != std::string::npos) {
            lineVector = split(line);
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

