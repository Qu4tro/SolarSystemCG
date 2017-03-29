#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/gl.h>

#include <unistd.h>
#include <math.h>

#include <vector>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <string>
#include <memory>

#include "EngineState.h"
#include "Command.h"
#include "XML.h"

#define MODEL_MAX_LINE_LENGTH 100

float cameraAlpha = 0;
float cameraBeta = 0;
float cameraDistance = 10;

void draw_triangles();
EngineState state;

void changeSize(int w, int h) {
    h = (h == 0) ? 1 : h;
    float ratio = w * 1.0 / h;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, w, h);
    gluPerspective(45.0f ,ratio, 1.0f ,1000.0f);

    glMatrixMode(GL_MODELVIEW);
}


void renderScene(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    auto pos = state.camera.cartesianPosition();
    auto focus = state.camera.cameraFocus;
    auto tilt = state.camera.cameraTilt;
    gluLookAt(std::get<0>(pos),    std::get<1>(pos),   std::get<2>(pos),
              std::get<0>(focus),  std::get<1>(focus), std::get<2>(focus),
              std::get<0>(tilt),   std::get<1>(tilt),  std::get<2>(tilt));


    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    state.applyCommands();
    glutSwapBuffers();
}


void keyboard(unsigned char key_code, int x, int y){
    switch(key_code) {
        case 'w':
            state.camera.cameraStepUp(); break;
        case 's':
            state.camera.cameraStepDown(); break;
    }
    glutPostRedisplay();
}


void specialkeyboard(int key_code, int x, int y){
    switch(key_code) {
        case GLUT_KEY_UP:
            state.camera.cameraStepForward(); break;
        case GLUT_KEY_DOWN:
            state.camera.cameraStepBackward(); break;
        case GLUT_KEY_LEFT:
            state.camera.cameraStepLeft(); break;
        case GLUT_KEY_RIGHT:
            state.camera.cameraStepRight(); break;
    }
    glutPostRedisplay();
}



int main(int argc, char** argv){
    if (argc <= 1){
        printf("Usage: %s scene.xml\n", argv[0]);
        return -1;
    }

    char command[256];
    sprintf(command, "./preprocess_xml %s", argv[1]);
    if (system(command) != 0){
        return 1;
    }
    FILE* scene_fp = fopen(argv[1], "r");

    state = EngineState();
    parse(scene_fp, state);
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(800,800);
    glutCreateWindow("CG");

    glewInit();

    glutDisplayFunc(renderScene);
    glutReshapeFunc(changeSize);

    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialkeyboard);

    /* if (vbo){ */
    /*   glEnableClientState(GL_VERTEX_ARRAY); */
    /*   glGenBuffers(1, buffers); */
    /*   glBindBuffer(GL_ARRAY_BUFFER, buffers[0]); */
    /*   glBufferData(GL_ARRAY_BUFFER, nVertices * sizeof(int), vertices, GL_STATIC_DRAW); */
    /*   glVertexPointer(3, GL_FLOAT, 0, 0); */
    /* } */

    glEnable(GL_DEPTH_TEST);
    /* glEnable(GL_CULL_FACE); */

    glutMainLoop();

    return 1;
}



