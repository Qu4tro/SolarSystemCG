#include "Models.h"

std::vector<std::string> split(std::string const &input) { 
    std::istringstream buffer(input);
    std::vector<std::string> ret {  std::istream_iterator<std::string>(buffer), 
                                    std::istream_iterator<std::string>()
                                 };
    return ret;
}

bool hasEnding (std::string const &fullString, std::string const &ending) {
    if (fullString.length() >= ending.length()) {
        return (0 == fullString.compare (fullString.length() - ending.length(), ending.length(), ending));
    } else {
        return false;
    }
}

std::vector<float> readSTL(std::string filename){
    std::vector<float> vertices;

    std::ifstream ifile(filename);
    std::string line;
    std::vector<std::string> lineVector;

    while (std::getline(ifile, line)) {
        if (line.find("vertex") != std::string::npos) {
            lineVector = split(line);
            vertices.push_back(stof(lineVector[1]));
            vertices.push_back(stof(lineVector[2]));
            vertices.push_back(stof(lineVector[3]));
        }
    }

    return vertices;
}


std::vector<float> readSimple(std::string filename){
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


std::vector<float> readModel(std::string model_path){
   if (hasEnding(model_path, ".stl")){
        return readSTL(model_path);
    } else {
        return readSimple(model_path);
    }
}
