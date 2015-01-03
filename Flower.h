
#include "Calculator.h"
#include <gl\glut.h>
#include <math.h>
#include <fstream>

const int FLOWER_MAX_LEVEL = 10;
const double LEAVE_STEP = 0.2;
using namespace std;
class Flower{
public:
    Flower(GLfloat x = 0, GLfloat y = 0, GLfloat z = -3.0, GLfloat _height = 3.0);
	void setCenterCount(int total, int* centerCnt);
	void setLeavesTexture(GLuint texture);
	void setFlowerTexture(GLuint texture);
	void setCenterTexture(GLuint texture);
    void setTextureType(int type);
    int getTextureType();

    void setFlowerType(int type){flowerType = type;}
    int getFlowerType(){return flowerType;}

	void setPosition(GLfloat x, GLfloat y, GLfloat z);
	void draw();
    void save(ofstream &ofs);
    void read(ifstream &ifs);

    GLfloat getHeight(GLfloat x, GLfloat z);
private:
	void drawLeaves();		//Please move to the root first!
	void drawFlower();			//Please move to the center first!
	void drawCenter();		//Please move to the center first!
    float modelOrig[16], modelTransform[16];
	Calculator cal;
	GLfloat rootX, rootY, rootZ;
	GLfloat height;
	GLuint centerLevel;
	int centerCount[FLOWER_MAX_LEVEL];
	GLuint leavesTexture, flowerTexture, centerTexture;
    int flowerTextureType, flowerType;
};
