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
            stringStream << "nVertices=";
            stringStream << nVertices;

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

struct TranslateT : Command {
    float tick, duration;
    std::vector<fTriple> points;
    TranslateT(float t, std::vector<fTriple> ps){
        tick = 0;
        duration = t;
        points = ps;
    }

    std::pair<fTriple, fTriple> getCatmullRomPoint(float, fTriple p0, fTriple p1, fTriple p2, fTriple p3){
        ; 
    }

    void apply(){
        if (tick == 1){
            tick = 0;
            points = std::vector<fTriple>(points.begin() + 1, points.end());
        }
        std::pair<fTriple, fTriple> vectors = getCatmullRomPoint(tick, points[0], points[1], points[2], points[3]);
        fTriple p = std::get<0>(vectors);
        fTriple v = std::get<1>(vectors);
        glTranslatef(p.x, p.y, p.z);
    }

    std::string toString(){
        std::ostringstream stringStream;
        stringStream << "TranslateT: ";
        stringStream << "Duration=" << duration << " ";
        stringStream << "Number of points=" << points.size() << " ";

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

struct RotateT : Command {
    float tick;
    float angle, axisX, axisY, axisZ;
    RotateT(float period, float x, float y, float z){
        tick = 0;
        angle = (2 * M_PI) / period;
        axisX = x;
        axisY = y;
        axisZ = z;
    }

    void apply(){
        glRotatef(tick * angle, axisX, axisY, axisZ);
        tick += 0.001;
    }
    std::string toString(){
        std::ostringstream stringStream;
        stringStream << "RotateT: ";

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
