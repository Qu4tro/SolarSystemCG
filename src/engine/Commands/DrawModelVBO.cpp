#include <sstream>
#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/gl.h>

#include "DrawModelVBO.h"

void DrawModelVBO::load(){
    nVertices = model -> getPoints().size();
    glGenBuffers(1, &geometry_array);
    glBindBuffer(GL_ARRAY_BUFFER, geometry_array);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * nVertices, &(model -> getPoints()[0]), GL_STATIC_DRAW);
}

DrawModelVBO::DrawModelVBO(Model* m){
    geometry_array = 0;
    indice_array = 0;
    model = m;
    model -> load();
    load();
}

void DrawModelVBO::apply(){
    glBindBuffer(GL_ARRAY_BUFFER, geometry_array);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, 0);
    glDrawArrays(GL_TRIANGLES, 0, nVertices);

    /* glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indice_array); */

    /* glEnableClientState(GL_TEXTURE_COORD_ARRAY); */
    /* glEnableClientState(GL_NORMAL_ARRAY); */

    /* glTexCoordPointer(3, GL_FLOAT, sizeof(GLfloat)*8, (float*)(sizeof(GLfloat)*5)); */
    /* glNormalPointer(GL_FLOAT, sizeof(GLfloat)*8, (float*)(sizeof(GLfloat)*3)); */

    /* glDrawElements(GL_TRIANGLES, num_indices, GL_UNSIGNED_INT, NULL); */

    glDisableClientState(GL_VERTEX_ARRAY);
    /* glDisableClientState(GL_NORMAL_ARRAY); */
    /* glDisableClientState(GL_TEXTURE_COORD_ARRAY); */

}

std::string DrawModelVBO::toString(){
    std::ostringstream stringStream;
    stringStream << "DrawModelVBO: ";
    stringStream << "file=";
    stringStream << model -> model_path;
    stringStream << std::endl;

    return stringStream.str();
}


