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
    float cameraX = cameraDistance * cos(cameraBeta) * sin(cameraAlpha);
    float cameraZ = cameraDistance * cos(cameraBeta) * cos(cameraAlpha);
    float cameraY = cameraDistance * sin(cameraBeta);
    gluLookAt(cameraX, cameraY, cameraZ,
            0.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f);


    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    state.applyCommands();
    glutSwapBuffers();
}


void keyboard(unsigned char key_code, int x, int y){
    float one_radian = M_PI / 360;
    int speed = 5;
    switch(key_code) {
        case 'o':
            cameraDistance += 0.1 * speed; break;
        case 'p':
            cameraDistance -= 0.1 * speed; break;
        case 'w':
            cameraBeta += one_radian * speed; break;
        case 's':
            cameraBeta -= one_radian * speed; break;
        case 'a':
            cameraAlpha += one_radian * speed; break;
        case 'd':
            cameraAlpha -= one_radian * speed; break;
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
    //glutSpecialFunc(rotate);

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



