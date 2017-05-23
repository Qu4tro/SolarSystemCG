#include "DrawModel.h"

DrawModel::DrawModel(Model* m){
    model = m;
}

void DrawModel::apply(){
    auto points = model -> getVertices();
    glBegin(GL_TRIANGLES);
    for(unsigned i = 0; i < points.size(); i += 3){
        glVertex3f(points[i], points[i + 1], points[i + 2]);
    }
    glEnd();
}

std::string DrawModel::toString(){
    std::ostringstream stringStream;
    stringStream << "DrawModel: ";
    stringStream << "file=";
    stringStream << model -> model_path;
    stringStream << std::endl;

    return stringStream.str();
}
