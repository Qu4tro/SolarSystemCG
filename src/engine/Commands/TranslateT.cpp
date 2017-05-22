#include "TranslateT.h"

TranslateT::TranslateT(float t, std::vector<fTriple> ps){
    gTick = 0;
    duration = t;
    points = ps;
}

TranslateT::TranslateT(float t){
    gTick = 0;
    duration = t;
}

void TranslateT::addPoint(float x, float y, float z){
    points.push_back(fTriple(x, y, z));
}

std::pair<fTriple, fTriple> TranslateT::catmullPoints(float t, fTriple p0, fTriple p1, fTriple p2, fTriple p3){

    std::vector<float> catmull = {-0.5f,  1.5f, -1.5f,  0.5f,
        1.0f, -2.5f,  2.0f, -0.5f,
        -0.5f,  0.0f,  0.5f,  0.0f,
        0.0f,  1.0f,  0.0f,  0.0f};

    std::vector<float> T = {t*t*t, t*t, t, 1};
    std::vector<float> dT = {3*t*t, 2*t, 1, 0};

    std::vector<float> TM = {0, 0, 0, 0};
    std::vector<float> dTM = {0, 0, 0, 0};

    fTriple position;
    fTriple derivative;

    for (int y = 0; y < 4; y++) { 
        for (int z = 0; z < 4; z++) {
            TM[y] +=  T[z] * catmull[4*z+y];
            dTM[y] += dT[z] * catmull[4*z+y];
        }
    }

    position.x = TM[0] * p0.x + TM[1] * p1.x + TM[2] * p2.x + TM[3] * p3.x;
    position.y = TM[0] * p0.y + TM[1] * p1.y + TM[2] * p2.y + TM[3] * p3.y;
    position.z = TM[0] * p0.z + TM[1] * p1.z + TM[2] * p2.z + TM[3] * p3.z;

    derivative.x = dTM[0] * p0.x + dTM[1] * p1.x + dTM[2] * p2.x + dTM[3] * p3.x;
    derivative.y = dTM[0] * p0.y + dTM[1] * p1.y + dTM[2] * p2.y + dTM[3] * p3.y;
    derivative.z = dTM[0] * p0.z + dTM[1] * p1.z + dTM[2] * p2.z + dTM[3] * p3.z;

    return std::make_pair(position, derivative);
}

std::pair<fTriple, fTriple> TranslateT::currentCatmull(float tick){
    int nPoints = points.size();
    float t = tick * nPoints;
    int index = floor(t);
    float baseT = t - index;

    return catmullPoints(baseT,
            points[(index - 1 + nPoints) % nPoints],
            points[(index     + nPoints) % nPoints],
            points[(index + 1 + nPoints) % nPoints],
            points[(index + 2 + nPoints) % nPoints]
            );
}

void TranslateT::trace() {
    glColor3f(1, 1, 1);
    float gtick = 0.0f;
    glBegin(GL_LINE_LOOP);
    while (gtick < 1.0f) {
        fTriple p = std::get<0>(currentCatmull(gtick));
        glVertex3f(p.x, p.y, p.z);
        gtick += 0.0001f;
    }
    glEnd();
}

void TranslateT::apply(){
    trace();
    std::pair<fTriple, fTriple> vectors = currentCatmull(gTick);
    fTriple p = std::get<0>(vectors);
    glTranslatef(p.x, p.y, p.z);
    /* fTriple v = std::get<1>(vectors); */
    /* curverotation v up*/

    /* equivalent to (wrapped to 1, to loop): gTick = glutGet(GLUT_ELAPSED_TIME) / 1000 / duration */
    gTick = fmod(glutGet(GLUT_ELAPSED_TIME) / (duration * 1000.0f), 1);
}

std::string TranslateT::toString(){
    std::ostringstream stringStream;
    stringStream << "TranslateT: ";
    stringStream << "time=" << duration << " ";
    stringStream << "points=" << "[";
    for(auto it: points){
        stringStream << it.toString();
    }
    stringStream << "]" << std::endl;

    return stringStream.str();
}


