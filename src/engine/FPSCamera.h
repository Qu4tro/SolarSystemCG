#ifndef FCAMERA_H
#define FCAMERA_H

#include "Camera.h"




class FPSCamera : public Camera {

    public:
        FPSCamera();
        ~FPSCamera();

        void move();

        fTriple position();
        fTriple focus();
        fTriple tilt();

        void specialkey(int key, bool pressed);
        void normalkey(unsigned char key, bool pressed);

    private:
        int specialKeys[128];
        char normalKeys[256];
        fTriple cameraPosition;
        fTriple cameraFront;
        fTriple cameraTilt;
        float cameraSpeed;
};

#endif
