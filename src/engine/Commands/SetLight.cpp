#include "SetLight.h"

SetLight::SetLight(fTriple p, bool ispoint){
	isPoint = ispoint;
	point = p;
}

void SetLight::apply(){

	GLfloat amb[4] = {0.1, 0.1, 0.1, 1};
	GLfloat diff[4] = {1, 1, 1, 0};
	GLfloat pos[4] = {point.x, point.y, point.z, (float) isPoint};

	glLightfv(GL_LIGHT0, GL_POSITION, pos);
	
	glLightfv(GL_LIGHT0, GL_AMBIENT, amb);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diff);
}
