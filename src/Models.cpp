#include "Models.h"

std::vector<std::string> split(std::string const &input) { 
    std::istringstream buffer(input);
    std::vector<std::string> ret {  std::istream_iterator<std::string>(buffer), 
                                    std::istream_iterator<std::string>()
                                 };
    return ret;
}

std::vector<float> readModel(std::string filename){
    int i;

    std::vector<float> vertices;

    std::ifstream ifile(filename);
    std::string line;
    std::vector<std::string> lineVector;

    while (std::getline(ifile, line)) {
        lineVector = split(line);
        vertices.push_back(stof(lineVector[0]));
        vertices.push_back(stof(lineVector[1]));
        vertices.push_back(stof(lineVector[2]));
    }

    return vertices;
}


