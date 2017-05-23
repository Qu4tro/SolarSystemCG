#ifndef BEZIER_H
#define BEZIER_H

#include <fstream>
#include <iterator>
#include <vector>
#include <string>
#include <math.h>
#include <assert.h>

#include "fTriple.h"
#include "Mesh.h"

#define BEZIER_N_VERTICES 16

class Bezier : public Mesh {

    public:
        Bezier(std::string bezier_file);
        Bezier(std::vector<fTriple> points, std::vector<int> indices);
        Bezier(std::vector<fTriple> points);

        std::string getObj();

    private:
        float B(int x, float u);
        std::vector<fTriple> controlPoints;
        std::vector<Bezier> patches;
        fTriple bezierSurface(float s, float t);

        int depth;
};

#endif
