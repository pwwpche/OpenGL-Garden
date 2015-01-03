
#include <gl/GLAUX.H>
#include <gl/glut.h>
#include <math.h>

const int C_FORWARD = 1;
const int C_BACKWARD = -1;
const int C_LEFT = 1;
const int C_RIGHT = 2;
const int C_UP = 3;
const int C_DOWN = 4;
const int C_FRONT = 5;
const int C_BACK = 6;
const int C_JMP = 7;

const int C_ON = 1;
const int C_OFF = 0;

const int C_TYPE_ANGLE = 1;
const int C_TYPE_DIRECTION = 2;
class Camera{
public:
	Camera();
    void move();
    void rotate();
    void changePerspective();
    void jump();
	void moveSwitch(int moveType, int opr);
	void continueMoving();
    double getJmpHeight();
	GLdouble get(char axis);
	GLdouble getLook(char axis);
    GLdouble getYRot();
	void setFixArea(int rad);
    void stop();
private:
	//Camera move
    GLdouble angleXZ, angleY;
	GLdouble lookX ,lookY, lookZ;
    double deltaAngle, deltaMove, deltaY;
    double jmpHeight, deltaJmp;
	GLfloat x,y, z;
	int fixedRad;
};
