#include "Flower.h"
#include <iostream>
using namespace std;
Flower::Flower(GLfloat x, GLfloat y, GLfloat z, GLfloat _height){
	rootX = x;
	rootY = y;
	rootZ = z;
	height = _height;
    flowerTextureType = 0;
    flowerType = 0;
}

void Flower::setCenterCount(int total, int* centerCnt){
	centerLevel = total;
	for(int i = 0;  i < total ; i++){
		centerCount[i] = centerCnt[i];
	}
}


void Flower::setTextureType(int type){
    flowerTextureType = type;
}

int Flower::getTextureType(){
    return flowerTextureType;
}

void Flower::setCenterTexture(GLuint texture){
	centerTexture = texture;
}

void Flower::setLeavesTexture(GLuint texture){
	leavesTexture = texture;
}

void Flower::setFlowerTexture(GLuint texture){
	flowerTexture = texture;
}
void Flower::setPosition(GLfloat x, GLfloat y, GLfloat z){
	rootX = x;
	rootY = y;
	rootZ = z;
}

GLfloat Flower::getHeight(GLfloat x, GLfloat z){
    float rad = sqrt((x - rootX ) * (x - rootX ) + (z - rootZ ) * (z - rootZ ));
    double centerRad = 0.2 + 1.7 * 0.4;
    if(rad < centerRad){
        return rootY + 2.0f - (centerRad - rad) / (centerRad) * 0.2;
    }else{
        double a = x - rootX;
        double b = z - rootZ;
        if(a > 0){
            if(((a-0.65) * (a-0.65) + b * b * 4) < 1)     //inside the leaves
            {
                double height = rootY + 0.7 + (a - 0.9) * 0.45 + 0.2  ;
                return height;
            }
        }else{
            a = -a;
            if(((a-0.65) * (a-0.65) + b * b * 4) < 1)     //inside the leaves
            {
                double height = rootY + 1.37 + (a - 0.9) * 0.45 + 0.2;
                return height;
            }
        }
        return rootY;
    }
}

void Flower::draw(){
    glGetFloatv(GL_MODELVIEW_MATRIX, modelOrig);
	glPushMatrix();
	glTranslatef(rootX, rootY, rootZ);
	glRotatef(-90, 1.0, 0.0, 0.0);
	glBindTexture(GL_TEXTURE_2D, leavesTexture);
	GLUquadricObj *quadratic;
    quadratic=gluNewQuadric();
    gluQuadricNormals(quadratic, GLU_SMOOTH);
    gluQuadricTexture(quadratic, GL_TRUE);

    gluCylinder(quadratic,0.1f,0.05f,2.0f,8,8);		//Brack
/*
    glBindTexture(GL_TEXTURE_2D, 0);
    for(float xx = -3.0 ; xx < 3.0 ; xx += 0.1){
        for(float zz = -1.5 ; zz < 1.5 ; zz += 0.1)
        {
            glTranslatef(-xx, zz, getHeight(rootX - xx, rootZ + zz) - rootY);
            gluSphere(quadratic,0.01f,8,8);		//Brack
            glTranslatef(xx, -zz, -getHeight(rootX - xx, rootZ + zz) + rootY);
        }
    }
    glBindTexture(GL_TEXTURE_2D, leavesTexture);
*/
	glBindTexture(GL_TEXTURE_2D, 0);
	glRotatef(90, 1.0, 0.0, 0.0);
	glTranslatef(0.0, 0.7, 0.0);
	drawLeaves();
	glRotatef(180, 0.0, 1.0, 0.0);	
	glTranslatef(0.0, 0.7, 0.0);
	drawLeaves();
	glRotatef(180, 0.0, 1.0, 0.0);

    glTranslatef(0.0, 0.4f, 0.0);
    drawCenter();
	drawFlower();

	glBindTexture(GL_TEXTURE_2D, 0);
	glColor3f(1, 1, 1);
	glPopMatrix();
}

void Flower::drawLeaves(){
	glPushMatrix();
    GLfloat a = 1, b = 0.5;
	glBindTexture(GL_TEXTURE_2D, leavesTexture);
	glTranslatef(a - 0.2 , 0, 0);
	glRotatef(30, 0.0, 0.0, 1.0);
	glBegin(GL_POLYGON);
    //Leave height is  0.1 * cal.mysin(( abs(x)+ a) / a * 3.14) + 0.7
    for(double theta = 0 ; theta < 2 * 3.14 ; theta += LEAVE_STEP){
		GLfloat x = a * cal.mycos (theta);
		GLfloat z = b * cal.mysin(theta);
		GLfloat y = 0.1 * cal.mysin((x+ a) / a * 3.14);
		glTexCoord2f(0.5 + x / 4.0, 0.25 + z / 4.0);
		glVertex3f(x, y, z);
	}
	glEnd();
	//glTranslatef(-a , 0, -b );
	glBindTexture(GL_TEXTURE_2D, 0);
	glPopMatrix();
}

void Flower::drawFlower(){

    //Base height is 1.4
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, flowerTexture);
    GLfloat a = 0.4, b = 0.1;//Control the shape of a flower
    if(flowerType == 1){
        b = 0.5;
    }
    //Just use top of first level of flower as its height.
    //and maximum tilt of first level is
    double alphaStep = 50.0 / centerLevel;      //Tilt degree of one level of flower
    unsigned int levelCnt = 0;
    //Flower part has the height of sin(60) * 2 * a
    //with a radius of 2 * a * cos(60)

    for(double alpha = 10.0; alpha < 60.0 && levelCnt < centerLevel; alpha += alphaStep, levelCnt++){
        GLfloat a0 = a * (60.0 - alpha) / 60.0 ;
        double phiStep = 360.0 / centerCount[levelCnt];     //Determined by number of pieces in a level
        phiStep = phiStep < 3 ? 3 : phiStep;
        for(double phi = 0 ; phi < 360 ; phi += phiStep){		//One level of flowers
			glPushMatrix();
			glRotatef(phi, 0.0, 1.0, 0.0);
			glTranslatef(0.2, 0.0, 0.0);
			glRotatef(alpha, 0.0, 0.0, 1.0);		//Rotate by Z axis
			glTranslatef( a0, 0.0, 0.0);
			glBegin(GL_POLYGON);
			for(double theta = 0 ; theta < 2 * 3.14 ; theta += LEAVE_STEP){
				GLfloat x = a0 * cal.mycos(theta);
				GLfloat z = b * cal.mysin(theta);
				GLfloat y = -0.05 * x * x;
				glTexCoord2f(0.5 + x / 4.0, 0.25 + z / 4.0);
				glVertex3f(x, y, z);
			}
			glEnd();			
			glPopMatrix();
		}
	}
	glBindTexture(GL_TEXTURE_2D, 0);		//Reset texture
	glPopMatrix();
}

void Flower::drawCenter(){
    glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, centerTexture);
	GLUquadricObj *qobj = gluNewQuadric();
	gluQuadricNormals(qobj,GLU_SMOOTH);
	gluQuadricTexture(qobj,GL_TRUE);
	glCullFace(GL_BACK);	
	glRotatef(90,1.0f,0.0f,0.0f);  //Important!
	gluSphere(qobj, 0.2, 32, 32);
	glBindTexture(GL_TEXTURE_2D, 0);		//Reset texture
	glColor3f(1.0f, 1.0f, 1.0f);
    glPopMatrix();
}

void Flower::save(ofstream &ofs){
    ofs << "Flower" << endl;
    ofs << rootX << " " << rootY << " " << rootZ << endl;
    ofs << height << " "<< flowerTextureType <<" "<< flowerType << endl;
    ofs << centerLevel << endl;
    for(size_t i = 0 ; i < centerLevel ; i++){
        ofs << centerCount[i] << " ";
    }
    ofs << endl;
}

void Flower::read(ifstream &ifs){
    ifs >> rootX >> rootY >> rootZ;
    ifs >> height >> flowerTextureType>> flowerType;
    ifs >> centerLevel ;
    for(size_t i = 0 ; i < centerLevel ; i++){
        ifs >> centerCount[i];
    }
}
