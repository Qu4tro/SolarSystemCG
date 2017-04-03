#include "Command.h"

struct EnterContext : Command {
    void apply(){
        glPushMatrix();
    }
    std::string toString(){
        return "EnterContext";
    }
};


struct ExitContext : Command {
    void apply(){
        glPopMatrix();
    }
    std::string toString(){
        return "ExitContext";
    }
};

struct DrawModel : Command {
    int index;
    std::vector<float> vertices;

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
        stringStream << "nVertices=";
        stringStream << vertices.size();

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

        return stringStream.str();
    }
};


