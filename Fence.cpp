#include "Fence.h"
Fence::Fence(GLfloat cx, GLfloat cy, GLfloat cz, GLfloat h, GLfloat w){
	centerX = cx;
	centerY = cy;
	centerZ = cz;
	height = h;
	width = w;
	fenceLength = 2;
	textureLoaded = false;
}

void Fence::setTexture(GLuint t){
	texture = t;
	textureLoaded = true;
}


void Fence::draw(){
	glPushMatrix();
	glColor3f(1, 1, 1);
	//Move center point
	glTranslatef(centerX, centerY, centerZ);
	//Draw Fence
	//Nearest Fence & farthest fence
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, texture);
	drawSideFrontBack();
	glPopMatrix();
	glRotatef( 90.0 , 0.0, 1.0, 0.0);
	drawSideLeftRight();
	glBindTexture(GL_TEXTURE_2D, 0);
	glColor3f(1, 1, 1);
	glPopMatrix();


}

void Fence::drawSideFrontBack(){
	float halfLen = fenceLength / 2;
	float fendwid = halfLen / 3;
	glTranslatef(-width / 2, height * 2 / 3 , -width / 2);		//Move to location of the first fence
	int baseCnt = 0;


	for(float i = 0 ; i <= width ; i += fenceLength){
		double baseHeight = frontHeight[baseCnt];
		glBegin(GL_QUADS);
			glTexCoord2f(1.0, 1.0);			glVertex3f(halfLen, fendwid + baseHeight, 0);
			glTexCoord2f(1.0, 0.0);			glVertex3f(halfLen, -fendwid + baseHeight, 0);
			glTexCoord2f(0.0, 0.0);			glVertex3f(-halfLen, -fendwid + baseHeight, 0);
			glTexCoord2f(0.0, 1.0);			glVertex3f(-halfLen, fendwid + baseHeight, 0);
		glEnd();

		glBegin(GL_POLYGON);
			glTexCoord2f(0.8, 0.8 );			glVertex3f(fendwid,height / 3.0 - fendwid / 2 + baseHeight , 0);
			glTexCoord2f(0.8, 0);			glVertex3f(fendwid, -height * 2.0 / 3.0 + baseHeight, 0);
			glTexCoord2f(0,0);			glVertex3f(-fendwid, -height * 2.0 / 3.0  + baseHeight, 0);
			glTexCoord2f(0, 0.8 );			glVertex3f(-fendwid,height / 3.0 - fendwid / 2 + baseHeight , 0);
			glTexCoord2f(0.4, 0.9);			glVertex3f(0, height / 3.0 + baseHeight , 0);
		glEnd();

		baseHeight = backHeight[baseCnt++];
		glBegin(GL_QUADS);
			glTexCoord2f(1.0, 1.0);			glVertex3f(halfLen, fendwid + baseHeight, width);
			glTexCoord2f(1.0, 0.0);			glVertex3f(halfLen, -fendwid + baseHeight, width);
			glTexCoord2f(0.0, 0.0);			glVertex3f(-halfLen, -fendwid + baseHeight, width);
			glTexCoord2f(0.0, 1.0);			glVertex3f(-halfLen, fendwid + baseHeight, width);
		glEnd();

		glBegin(GL_POLYGON);
			glTexCoord2f(0.8, 0.8 );			glVertex3f(fendwid,height / 3.0 - fendwid / 2 + baseHeight , width);
			glTexCoord2f(0.8, 0);			glVertex3f(fendwid, -height * 2.0 / 3.0 + baseHeight, width);
			glTexCoord2f(0,0);			glVertex3f(-fendwid, -height * 2.0 / 3.0 + baseHeight, width);
			glTexCoord2f(0, 0.8 );			glVertex3f(-fendwid,height / 3.0 - fendwid / 2 + baseHeight , width);
			glTexCoord2f(0.4, 0.9);			glVertex3f(0, height / 3.0 + baseHeight , width);
		glEnd();
		glTranslatef(fenceLength, 0, 0);
	}
}

void Fence::drawSideLeftRight(){
	float halfLen = fenceLength / 2;
	float fendwid = halfLen / 3;
	glTranslatef(-width / 2, height * 2 / 3 , -width / 2);		//Move to location of the first fence
	int baseCnt = 0;


	for(float i = 0 ; i <= width ; i += fenceLength){
		double baseHeight = leftHeight[baseCnt];
		glBegin(GL_QUADS);
			glTexCoord2f(1.0, 1.0);			glVertex3f(halfLen, fendwid + baseHeight, 0);
			glTexCoord2f(1.0, 0.0);			glVertex3f(halfLen, -fendwid + baseHeight, 0);
			glTexCoord2f(0.0, 0.0);			glVertex3f(-halfLen, -fendwid + baseHeight, 0);
			glTexCoord2f(0.0, 1.0);			glVertex3f(-halfLen, fendwid + baseHeight, 0);
		glEnd();

		glBegin(GL_POLYGON);
			glTexCoord2f(0.8, 0.8 );			glVertex3f(fendwid,height / 3.0 - fendwid / 2 + baseHeight , 0);
			glTexCoord2f(0.8, 0);			glVertex3f(fendwid, -height * 2.0 / 3.0 + baseHeight, 0);
			glTexCoord2f(0,0);			glVertex3f(-fendwid, -height * 2.0 / 3.0  + baseHeight, 0);
			glTexCoord2f(0, 0.8 );			glVertex3f(-fendwid,height / 3.0 - fendwid / 2 + baseHeight , 0);
			glTexCoord2f(0.4, 0.9);			glVertex3f(0, height / 3.0 + baseHeight , 0);
		glEnd();

		baseHeight = rightHeight[baseCnt++];
		glBegin(GL_QUADS);
			glTexCoord2f(1.0, 1.0);			glVertex3f(halfLen, fendwid + baseHeight, width);
			glTexCoord2f(1.0, 0.0);			glVertex3f(halfLen, -fendwid + baseHeight, width);
			glTexCoord2f(0.0, 0.0);			glVertex3f(-halfLen, -fendwid + baseHeight, width);
			glTexCoord2f(0.0, 1.0);			glVertex3f(-halfLen, fendwid + baseHeight, width);
		glEnd();

		glBegin(GL_POLYGON);
			glTexCoord2f(0.8, 0.8 );			glVertex3f(fendwid,height / 3.0 - fendwid / 2 + baseHeight , width);
			glTexCoord2f(0.8, 0);			glVertex3f(fendwid, -height * 2.0 / 3.0 + baseHeight, width);
			glTexCoord2f(0,0);			glVertex3f(-fendwid, -height * 2.0 / 3.0 + baseHeight, width);
			glTexCoord2f(0, 0.8 );			glVertex3f(-fendwid,height / 3.0 - fendwid / 2 + baseHeight , width);
			glTexCoord2f(0.4, 0.9);			glVertex3f(0, height / 3.0 + baseHeight , width);
		glEnd();
		glTranslatef(fenceLength, 0, 0);
	}
}

void Fence::setHeight(vector<double> h1, vector<double> h2, vector<double> h3, vector<double> h4){
	frontHeight = h1;
	backHeight = h2;
	leftHeight = h3;
	rightHeight = h4;
}

int Fence::getLength(){
	return fenceLength;
}

int Fence::getSize(){
	return width;
}
