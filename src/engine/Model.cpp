#include <iostream>
#include <iterator>
#include <fstream>
#include <sstream>

#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"

#include "Model.h"

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

void vertex_cb(void *user_data, float x, float y, float z, float w) {
  Model *model = reinterpret_cast<Model *>(user_data);

  model->vertices.push_back(x);
  model->vertices.push_back(y);
  model->vertices.push_back(z);
}

void normal_cb(void *user_data, float x, float y, float z) {
  Model *model = reinterpret_cast<Model *>(user_data);

  model->normals.push_back(x);
  model->normals.push_back(y);
  model->normals.push_back(z);
}

void texcoord_cb(void *user_data, float x, float y, float z) {
  Model *model = reinterpret_cast<Model *>(user_data);

  model->texcoords.push_back(x);
  model->texcoords.push_back(y);
  model->texcoords.push_back(z);
}

void index_cb(void *user_data, tinyobj::index_t *indices, int num_indices) {
  Model *model = reinterpret_cast<Model *>(user_data);

  for (int i = 0; i < num_indices; i++) {
    tinyobj::index_t idx = indices[i];
    printf("idx[%ld] = %d, %d, %d\n", model->v_indices.size(), idx.vertex_index, idx.normal_index, idx.texcoord_index);

    if (idx.vertex_index != 0) {
      model->v_indices.push_back(idx.vertex_index);
    }
    if (idx.normal_index != 0) {
      model->vn_indices.push_back(idx.normal_index);
    }
    if (idx.texcoord_index != 0) {
      model->vt_indices.push_back(idx.texcoord_index);
    }
  }
}

void Model::load(std::string filename){

  tinyobj::callback_t cb;
  cb.vertex_cb = vertex_cb;
  cb.normal_cb = normal_cb;
  cb.texcoord_cb = texcoord_cb;
  cb.index_cb = index_cb;

  Model mesh;
  std::string err;
  std::ifstream ifs(filename.c_str());
  bool ret = tinyobj::LoadObjWithCallback(ifs, cb, &mesh, NULL, &err);
  if (!err.empty()) {
    std::cerr << err << std::endl;
  }
}

Model::Model(){
    ;
}

Model::Model(std::string path){
    filename = path;
}

