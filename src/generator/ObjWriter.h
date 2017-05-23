#ifndef OBJ_WRITER_H
#define OBJ_WRITER_H

#include <string>
#include <sstream>

class ObjWriter {

    public:
        ObjWriter();
        unsigned addVertex(float, float, float);
        unsigned addNormal(float, float, float);
        unsigned addTexture(float, float);

        void makeTriangle();
        void makeQuad();

        std::string toString();

    private:
        std::ostringstream objStream;


};

#endif
