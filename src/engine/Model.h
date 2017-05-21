#ifndef MODEL_H
#define MODEL_H

#include <vector>
#include <string>

struct Model {
    Model();
    Model(std::string path);

    void load(std::string filename);
    std::string filename;

    std::vector<float> vertices; 
    std::vector<float> texcoords; 
    std::vector<float> normals;
    std::vector<int> v_indices;
    std::vector<int> vn_indices;
    std::vector<int> vt_indices;
};


#endif
