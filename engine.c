#include <GL/glut.h>
#include <GL/gl.h>

#include <stdio.h>
#include <math.h>
#include <assert.h>

#include "errors.h"
#include "utils.h"

#define MODEL_MAX_LINE_LENGTH 100



int read_model(char* filename, float* vertices, int* n){

    char* line = malloc(sizeof(char) * MODEL_MAX_LINE_LENGTH);
    char** separatedLine;

    FILE* modelfp = fopen(filename, "r");

    *n = 0;

    while (fgets(line, MODEL_MAX_LINE_LENGTH, modelfp)){

        separatedLine = split(strtok(line, "\r\n"));
        assert(nParams(separatedLine) == 3);

        //validar
        vertices[*n] = atof(separatedLine[*n % 3]);

        //to debug
        if (vertices[*n] == 0){
            printf("Atof got zero: %s\n", separatedLine[*n % 3]);
        }
    }
    
    return NO_ERROR;
}

int load_scene(char* xml_scene_filename);


void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window with zero width).
	if (h == 0){
		h = 1;
    }

	// compute window's aspect ratio 
	float ratio = w * 1.0 / h;

	// Set the projection matrix as current
	glMatrixMode(GL_PROJECTION);
	// Load Identity Matrix
	glLoadIdentity();
	
	// Set the viewport to be the entire window
    glViewport(0, 0, w, h);

	// Set perspective
	gluPerspective(45.0f ,ratio, 1.0f ,1000.0f);

	// return to the model view matrix mode
	glMatrixMode(GL_MODELVIEW);
}


void renderScene(void) {

	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set the camera
	glLoadIdentity();
	gluLookAt(0.0,5.0,-1.0, 
		      0.0,0.0,0.0,
			  0.0f,1.0f,0.0f);

// put the geometric transformations here


    glBegin(GL_TRIANGLES);

 	//front
    glVertex3f(-1.0f, 0.0f, 1.0f);
    glVertex3f(1.0f, 0.0f, 1.0f);
    glVertex3f(0.0f, 1.0f, 0.0f);

    glVertex3f(1.0f, 0.0f, 1.0f);
    glVertex3f(-1.0f, 0.0f, -1.0f);
    glVertex3f(-1.0f, 0.0f, 1.0f);

    //bottom right
    glVertex3f(1.0f, 0.0f, 1.0f);
    glVertex3f(1.0f, 0.0f, -1.0f);
    glVertex3f(-1.0f, 0.0f, -1.0f);

    //right
    glVertex3f(1.0f, 0.0f, 1.0f);
    glVertex3f(1.0f, 0.0f, -1.0f);
    glVertex3f(0.0f, 1.0f, 0.0f);

    //back
    glVertex3f(1.0f, 0.0f, -1.0f);
    glVertex3f(-1.0f, 0.0f, -1.0f);
    glVertex3f(0.0f, 1.0f, 0.0f);

    //left
    glVertex3f(-1.0f, 0.0f, 1.0f);
    glVertex3f(0.0f, 1.0f, 0.0f);
    glVertex3f(-1.0f, 0.0f, -1.0f);

    glEnd();

    // put drawing instructions here
    glPolygonMode(GL_FRONT, GL_POINT);

	// End of frame
	glutSwapBuffers();
}



// write function to process keyboard events

/*
	if(key_code == GLUT_KEY_UP)


}
*/


// write function to process menu events




int main(int argc, char **argv){

    int n = 0;
    float* vertices;

    if (argc <= 1){
        printf("Precisa de ter um ficheiro xml como argumento.");
        return -1;
    } 

    /* load_scene(argv[1]); */
    
    read_model("teste.txt", vertices, &n);

    int i;
    for (i = 0; i < n; i += 3) {
        printf("Ponto: "); 
        printf("%f %f %f\n", vertices[i],
                             vertices[i+1],
                             vertices[i+2]); 
    }

    return 0;

// init GLUT and the window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(800,800);
    glutCreateWindow("CG@DI-UM");
		

// Required callback registry 
    glutDisplayFunc(renderScene);
    glutReshapeFunc(changeSize);

// put here the registration of the keyboard and menu callbacks

    //glutSpecialFunc(rotate);

// put here the definition of the menu 


//  OpenGL settings
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
	
// enter GLUT's main cycle
    glutMainLoop();
	
	return 1;
}

