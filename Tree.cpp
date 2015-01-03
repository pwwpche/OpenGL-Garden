#include "Tree.h"

#define TREE_ANGLE 0.2
#define TREE_SCALE 0.9
#define TREE_RAND 0.01

Tree::Tree(double _height, double _width, int _levels){
	height = _height > 5.0 ? _height : 5.0;
	height = _height < 25.0 ? _height : 25.0;
	width = _width > 6.0 ? 6.0 : _width;
	width = _width < 2.0 ? 2.0 : _width;
	levels = _levels > 8 ? 8 : _levels;
	levels = _levels < 3 ? 3 : _levels;
}
void Tree::setPosition(GLfloat x, GLfloat y, GLfloat z){
	rootX = x;
	rootY = y;
	rootZ = z;
}


void Tree::draw()
{
	// Draw tree
	glPushMatrix();

    glTranslatef(rootX, rootY, rootZ);
	glRotatef(-90, 1.0, 0.0, 0.0);



	//glColor3f(0.0, 1.0, 0.0);
	glBindTexture(GL_TEXTURE_2D, brackTexture);



	GLUquadricObj *quadratic;
    quadratic=gluNewQuadric();
    gluQuadricNormals(quadratic, GLU_SMOOTH);
    gluQuadricTexture(quadratic, GL_TRUE);
/*
    for(float xx = -width ; xx < width ; xx += 0.1){
        for(float zz = -width ; zz < width ; zz += 0.1){
            glTranslatef(xx, zz, getHeight(rootX + xx, rootZ + zz) - rootY);
            gluCylinder(quadratic,0.05f,0.05f,0.2,2,1);		//Brack
            glTranslatef(-xx, -zz, -getHeight(rootX + xx, rootZ + zz) + rootY);
        }
    }
*/
    gluCylinder(quadratic,0.5f,0.2f,height * 0.4,32,32);		//Brack
	glTranslatef(0.0, 0.0, height * 0.3);
	glBindTexture(GL_TEXTURE_2D, topTexture);		//Tree leaves
    double curHeight = height * 0.6, curWidth = width;
	for(int i = 0 ; i < levels ; i++){
        gluCylinder(quadratic,curWidth,0.0f,curHeight,32,32);
        glTranslatef(0.0, 0.0, curHeight * 0.8);
        curHeight = curHeight / 2;
		curWidth = curWidth / 2;
    }
	glBindTexture(GL_TEXTURE_2D, 0);
	glColor3f(1, 1, 1);
	glPopMatrix();
}

double Tree::getHeight(GLfloat x, GLfloat z){
    double rad = sqrt((x - rootX) * (x - rootX) + (z - rootZ) * (z - rootZ));
    double rad0 = rad, heightRatio =0.8, levelHeight = 0.6 * height, levelWidth = width;
    int levelCnt = 0;
    double baseHeight = rootY;
    if(rad > width){
        return baseHeight;
    }else{
        baseHeight += 0.3 * height;
        //find which level it is in
        while(rad * 2 < width && levelCnt < levels){
            rad = rad * 2;
            baseHeight += levelHeight * heightRatio;
            levelHeight *= 0.5;
            levelWidth *= 0.5;
            levelCnt++;
        }
        if(levelCnt < levels){
            baseHeight += (levelWidth-rad0) / levelWidth * levelHeight;
        }else{
            baseHeight += (width / 4 -rad ) / width * levelHeight;
        }
    }
    return baseHeight + 0.1;
}

void Tree::setTexture(GLuint brack, GLuint top){
	brackTexture = brack;
	topTexture = top;
}

void Tree::save(ofstream &ofs){
    ofs << "Tree" << endl;
    ofs << rootX << " " << rootY << " " << rootZ << endl;
    ofs << height << " " << width << " " << levels << endl;
    ofs << endl;
}

void Tree::read(ifstream &ifs){
    ifs >> rootX >> rootY >> rootZ;
    ifs >> height >> width >> levels ;
}
