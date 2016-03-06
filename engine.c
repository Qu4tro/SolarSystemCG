#include <GL/glut.h>
#include <GL/gl.h>

#include <stdio.h>
#include <math.h>
#include <assert.h>

#include "errors.h"
#include "utils.h"
#include "xmlParser.h"

#define MODEL_MAX_LINE_LENGTH 100


int read_model(char* filename, float* vertices, int* n){

    int i;

    char* line = malloc(sizeof(char) * MODEL_MAX_LINE_LENGTH);
    char** separatedLine;

    FILE* modelfp = fopen(filename, "r");

    if (modelfp == NULL){
        puts("Can't open file");
        exit(1);
    }


    while (fgets(line, MODEL_MAX_LINE_LENGTH, modelfp)){

        separatedLine = split(strtok(line, "\r\n"));
        assert(nParams(separatedLine) == 3);

        // needs validation? TODO
        for (i = 0; i < 3; ++i) {
            vertices[*n] = atof(separatedLine[i]);
            *n += 1;
        }
    }

    /* for (i = 0; i < *n; ++i) { */
    /*     printf("%f ", vertices[i]); */
    /*     if (i % 3 == 2){ */
    /*         printf("\n"); */
    /*     } */
    /* } */
    
    return NO_ERROR;
}


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
    ; 

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    glBegin(GL_TRIANGLES);



    glEnd();

    // put drawing instructions here

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

    int i;
    int n = 0;
    float* vertices;
    char** filenames;

    if (argc <= 1){
        printf("Usage: %s scene.xml\n", argv[0]);
        return -1;
    } 

    filenames = getModels(argv[1]);
    vertices = malloc(sizeof(float) * 5000); //TODO

    for (i = 0; filenames[i] != NULL; ++i) {
        read_model(filenames[i], vertices, &n);
    }

    printf("%d\n", n);
    for (i = 0; i < n; i += 3) {
        printf("%f %f %f\n", vertices[i],
                             vertices[i + 1],
                             vertices[i + 2]); 
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

