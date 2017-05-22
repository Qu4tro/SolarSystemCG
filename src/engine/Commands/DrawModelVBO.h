#pragma once

#include "../Model.h"
#include "Command.h"
#include <GL/glew.h>
/* #include <GL/glut.h> */
/* #include <GL/gl.h> */


class DrawModelVBO : public Command {
    private:
        int nVertices;
        GLuint geometry_array;
        GLuint indice_array;

        void load();

    public:
        Model* model;

        DrawModelVBO(Model*);

        void apply();
        std::string toString();
};

