#ifndef OCAMERA_H
#define OCAMERA_H

#include <algorithm>
#include <math.h>

#include "Camera.h"

class OrbitalCamera : public Camera {

    public:
        OrbitalCamera();
        ~OrbitalCamera();

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
        fTriple cameraFocus;
        fTriple cameraTilt;
        float cameraSpeed;
};

#endif
