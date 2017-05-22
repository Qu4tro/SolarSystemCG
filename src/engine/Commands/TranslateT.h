#pragma once

#include <vector>
#include <sstream>
#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/gl.h>

#include <math.h>
#include <utility>

#include "Command.h"
#include "../fTriple.h"

class TranslateT : public Command {

    private:
        std::pair<fTriple, fTriple> catmullPoints(float t, fTriple p0, fTriple p1, fTriple p2, fTriple p3);
        std::pair<fTriple, fTriple> currentCatmull(float tick);
        float gTick, duration;

    public:
        TranslateT(float t, std::vector<fTriple> ps);
        TranslateT(float t);

        void addPoint(float x, float y, float z);
        void trace();
        
        void apply();
        std::string toString();

        std::vector<fTriple> points;

};

