#pragma once

#include "../Model_3D.h"
#include "Command.h"
#include <GL/glew.h>
#include <assert.h>
/* #include <GL/glut.h> */
/* #include <GL/gl.h> */


class DrawModelVBO : public Command {
    private:
        int nVertices;
        GLuint geometry_array;
        GLuint indice_array;

        void load();

    public:
        Model_3D model;

        DrawModelVBO(Model_3D);

        void apply();
        std::string toString();
};

