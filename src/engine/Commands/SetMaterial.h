#pragma once

#include "Command.h"
#include <sstream>
#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/gl.h>

#include "../fTriple.h"

struct SetMaterial : Command {
    bool isDiffuse;
    float diff_or_amb[4];
    float specular[4];
    float emissive[4];
    float ambient[4];
    float shininess;

    SetMaterial(float shiny);
    void setDiffuse(fTriple);
    void setAmbient(fTriple);
    void setSpecular(fTriple);
    void setEmissive(fTriple);
    void apply();
    std::string toString();
};

