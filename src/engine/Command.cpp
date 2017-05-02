#ifndef COMMANDS_CPP
#define COMMANDS_CPP

#include "Command.h"

struct EnterContext : Command {
    void apply(){
        glPushMatrix();
    }
    std::string toString(){
        std::ostringstream stringStream;
        stringStream << "EnterContext";
        stringStream << std::endl;

        return stringStream.str();
    }

};

struct ExitContext : Command {
    void apply(){
        glPopMatrix();
    }
    std::string toString(){
        std::ostringstream stringStream;
        stringStream << "ExitContext";
        stringStream << std::endl;

        return stringStream.str();
    }
};

class DrawModelVBO : public Command {

    private:
        int nVertices;
        std::string model_path;
        GLuint geometry_array;
        GLuint indice_array;

        void loadVertices(){
            std::vector<float> vertices = readModel(model_path);
            nVertices = vertices.size();
            glGenBuffers(1, &geometry_array);
            glBindBuffer(GL_ARRAY_BUFFER, geometry_array);
            glBufferData(GL_ARRAY_BUFFER, sizeof(float) * nVertices, &vertices[0], GL_STATIC_DRAW);
        }

    public:
        DrawModelVBO(std::string path){
            geometry_array = 0;
            indice_array = 0;
            model_path = path;
            loadVertices();
        }

        void apply(){
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

        std::string toString(){
            std::ostringstream stringStream;
            stringStream << "DrawModelVBO: ";
            stringStream << "file=";
            stringStream << model_path;
            stringStream << std::endl;

            return stringStream.str();
        }
};

class DrawModel : public Command {

    private:
        std::vector<float> vertices;

    public:
        std::string model_path;

        DrawModel(std::string path){
            model_path = path;
            vertices = readModel(model_path);
        }

        void apply(){
            glBegin(GL_TRIANGLES);
            for(unsigned i = 0; i < vertices.size(); i += 3){
                glVertex3f(vertices[i], vertices[i + 1], vertices[i + 2]);
            }
            glEnd();
        }

        std::string toString(){
            std::ostringstream stringStream;
            stringStream << "DrawModel: ";
            stringStream << "file=";
            stringStream << model_path;
            stringStream << std::endl;

            return stringStream.str();
        }
};

struct Color : Command {
    float R, G, B;

    Color(float r, float g, float b){
        R = r;
        G = g;
        B = b;
    }

    void apply(){
        glColor3f(R, G, B);
    }

    std::string toString(){
        std::ostringstream stringStream;
        stringStream << "Color: ";
        stringStream << "R=" << R << " ";
        stringStream << "G=" << G << " ";
        stringStream << "B=" << B << " ";
        stringStream << std::endl;

        return stringStream.str();
    }
};

struct Translate : Command {
    float X, Y, Z;
    Translate(float x, float y, float z){
        X = x;
        Y = y;
        Z = z;
    }

    void apply(){
        glTranslatef(X, Y, Z);
    }


    std::string toString(){
        std::ostringstream stringStream;
        stringStream << "Translate: ";
        stringStream << "X=" << X << " ";
        stringStream << "Y=" << Y << " ";
        stringStream << "Z=" << Z << " ";
        stringStream << std::endl;

        return stringStream.str();
    }
};

struct TranslateT : Command {
    float gTick, duration;
    std::vector<fTriple> points;
    TranslateT(float t, std::vector<fTriple> ps){
        float gtick = 0.0f;
        while (gtick < 1.0f) {
            fTriple p = std::get<0>(currentCatmull(gtick));
            std::cout << p.toString() << std::endl;
            gtick += 0.0001f;
        }

        gTick = 0;
        duration = t;
        points = ps;
    }
    TranslateT(float t){
        gTick = 0;
        duration = t;
    }

    void addPoint(float x, float y, float z){
        points.push_back(fTriple(x, y, z));
    }

    std::pair<fTriple, fTriple> catmullPoints(float t, fTriple p0, fTriple p1, fTriple p2, fTriple p3){

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

    std::pair<fTriple, fTriple> currentCatmull(float tick){
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

    void trace() {
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

    void apply(){
        trace();
        std::pair<fTriple, fTriple> vectors = currentCatmull(gTick);
        fTriple p = std::get<0>(vectors);
        glTranslatef(p.x, p.y, p.z);
        /* fTriple v = std::get<1>(vectors); */
        /* curverotation v up*/

        /* equivalent to (wrapped to 1, to loop): gTick = glutGet(GLUT_ELAPSED_TIME) / 1000 / duration */
        gTick = fmod(glutGet(GLUT_ELAPSED_TIME) / (duration * 1000.0f), 1);
    }

    std::string toString(){
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
};

struct Rotate : Command {
    float angle, axisX, axisY, axisZ;
    Rotate(float ang, float x, float y, float z){
        angle = ang;
        axisX = x;
        axisY = y;
        axisZ = z;
    }

    void apply(){
        glRotatef(angle, axisX, axisY, axisZ);
    }
    std::string toString(){
        std::ostringstream stringStream;
        stringStream << "Rotate: ";

        stringStream << "angle=" << angle << " ";
        stringStream << "axisX=" << axisX << " ";
        stringStream << "axisY=" << axisY << " ";
        stringStream << "axisZ=" << axisZ << " ";
        stringStream << std::endl;

        return stringStream.str();
    }
};

struct RotateT : Command {
    float period;
    float axisX, axisY, axisZ;
    RotateT(float p, float x, float y, float z){
        period = p;
        axisX = x;
        axisY = y;
        axisZ = z;
    }

    void apply(){
        /* float angle = fmod((glutGet(GLUT_ELAPSED_TIME) / 1000.0f ) * (360.0f / period), 360.0f); */
        float angle = fmod((glutGet(GLUT_ELAPSED_TIME) * 360.0f ) / (period * 1000.0f), 360.0f);
        glRotatef(angle, axisX, axisY, axisZ);
    }

    std::string toString(){
        std::ostringstream stringStream;
        stringStream << "RotateT: ";

        stringStream << "time="   << period << " ";
        stringStream << "axisX="  << axisX  << " ";
        stringStream << "axisY="  << axisY  << " ";
        stringStream << "axisZ="  << axisZ  << " ";
        stringStream << std::endl;

        return stringStream.str();
    }
};

struct Scale : Command {
    float X, Y, Z;
    Scale(float x, float y, float z){
        X = x;
        Y = y;
        Z = z;
    }

    void apply(){
        glScalef(X, Y, Z);
    }
    std::string toString(){
        std::ostringstream stringStream;
        stringStream << "Scale: ";
        stringStream << "X=" << X << " ";
        stringStream << "Y=" << Y << " ";
        stringStream << "Z=" << Z << " ";
        stringStream << std::endl;

        return stringStream.str();
    }
};

#endif
