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
#include "Commands/Command.h"
#include "SceneParser.h"

#define MODEL_MAX_LINE_LENGTH 100

EngineState state;
int timebase = 0;
int frame = 0;

void changeSize(int w, int h) {
    h = (h == 0) ? 1 : h;
    float ratio = w * 1.0 / h;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, w, h);
    gluPerspective(45.0f ,ratio, 1.0f ,1000.0f);

    glMatrixMode(GL_MODELVIEW);
}

void displayFPS() {
	int time;
	char title[20];

	frame++;
	time = glutGet(GLUT_ELAPSED_TIME);
	if (time - timebase > 1000) {
		float fps = frame * 1000.0/(time - timebase);
		timebase = time;
		frame = 0;
		sprintf(title,"CG  |  %.2f FPS",fps);
		glutSetWindowTitle(title);
  }
}

void renderScene(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    auto pos = state.camera   -> position();
    auto focus = state.camera -> focus();
    auto tilt = state.camera  -> tilt();
    gluLookAt(  pos.x,   pos.y,   pos.z,
              focus.x, focus.y, focus.z,
               tilt.x,  tilt.y,  tilt.z);

    state.camera -> move();
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    state.applyCommands();
    displayFPS();
    glutSwapBuffers();
}

void keyboard(unsigned char key_code, int x, int y){
    state.camera -> normalkey(key_code, true);
    glutPostRedisplay();
}
void upkeyboard(unsigned char key_code, int x, int y){
    state.camera -> normalkey(key_code, false);
    glutPostRedisplay();
}
void specialkeyboard(int key_code, int x, int y){
    state.camera -> specialkey(key_code, true);
    glutPostRedisplay();
}
void upspecialkeyboard(int key_code, int x, int y){
    state.camera -> specialkey(key_code, false);
    glutPostRedisplay();
}

void inits(){
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(800, 800);
    glutCreateWindow("CG");

    glewInit();

    glutDisplayFunc(renderScene);
    glutIdleFunc(renderScene);
    glutReshapeFunc(changeSize);

    glutKeyboardFunc(keyboard);
    glutKeyboardUpFunc(upkeyboard);
    glutSpecialFunc(specialkeyboard);
    glutSpecialUpFunc(upspecialkeyboard);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glEnable(GL_NORMALIZE);
    glEnable(GL_LIGHTING);
}

int main(int argc, char** argv){

    if (argc <= 1){
        printf("Usage: %s scene.xml\n", argv[0]);
        return -1;
    }

    glutInit(&argc, argv);
    inits();


    state = EngineState();
    state.setSceneCommands(parse_scene(argv[1]));
    /* state.VBOify(); */
    state.printCommands();

    glutMainLoop();

    return 1;
}



