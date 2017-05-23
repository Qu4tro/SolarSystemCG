#include "DrawModel.h"

DrawModel::DrawModel(Model_3D m){
    assert(model.loaded() == false);
    model = m;
}

void DrawModel::apply(){
    if (model.loaded() == false){
        model.load();
    }
    auto vertices = model.getVertices();
    auto normals = model.getNormals();
    assert(vertices.size() == normals.size() || normals.size() == 0);
    glBegin(GL_TRIANGLES);
    for(unsigned i = 0; i < vertices.size(); i += 3){
        if (normals.size() != 0)
            glNormal3f(normals[i], normals[i + 1], normals[i + 2]);
        glVertex3f(vertices[i], vertices[i + 1], vertices[i + 2]);
    }
    glEnd();
}

std::string DrawModel::toString(){
    std::ostringstream stringStream;
    stringStream << "DrawModel: ";
    stringStream << "file=";
    stringStream << model.getPath();
    stringStream << std::endl;

    return stringStream.str();
}
