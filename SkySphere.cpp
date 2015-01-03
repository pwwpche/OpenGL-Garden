#include "SkySphere.h"

void SkySphere::draw(GLuint texture){
	//Set up sky texture
	glBindTexture(GL_TEXTURE_2D, texture);

	GLUquadricObj *qobj = gluNewQuadric();
	gluQuadricNormals(qobj,GLU_SMOOTH);
	gluQuadricTexture(qobj,GL_TRUE);

	glRotatef(90,1.0f,0.0f,0.0f);  //Important!
    glRotatef(rotation, 0.0, 0.0, 1.0);
    rotation += 0.02;
	gluSphere(qobj, 200, 32, 32);
	glBindTexture(GL_TEXTURE_2D, 0);		//Reset texture
	glColor3f(1.0f, 1.0f, 1.0f);


}
