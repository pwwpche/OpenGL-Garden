
#include "Camera.h"
#include <iostream>
using namespace std;
Camera::Camera(){
    angleXZ = 0;  	angleY = 0;
    deltaAngle = 0; deltaMove = 0, deltaY = 0;
	lookX = 0; 	lookY = 0; 	lookZ = -1;
	x = 0;	y = 10;	z = 0;
	fixedRad = 0;
    jmpHeight = 0, deltaJmp = 0;
}

void Camera::move(){
            if(fixedRad == 0){
                x += lookX * 0.1 * deltaMove;
                z += lookZ * 0.1 * deltaMove;
            }else{
                x = x + lookX * 0.1 * deltaMove > fixedRad ? fixedRad :  x + lookX * 0.1 * deltaMove;
                x = x + lookX * 0.1 * deltaMove < -fixedRad ? -fixedRad :  x + lookX * 0.1 * deltaMove;
                z = z +  lookZ * 0.1 * deltaMove> fixedRad ? fixedRad :  z +  lookZ * 0.1 * deltaMove;
                z = z +  lookZ * 0.1 * deltaMove< -fixedRad ? -fixedRad :  z +  lookZ * 0.1 * deltaMove;
            }
}

void Camera::stop(){
    deltaAngle = 0;
    deltaMove = 0;
    deltaY = 0;
    deltaJmp = 0;
}

void Camera::moveSwitch(int moveType, int opr){
    switch(moveType){
    case C_LEFT:
        if(opr == C_ON){
            deltaAngle += -0.01;
        }else if (opr == C_OFF){
            //deltaAngle  += 0.01;
            deltaAngle = 0;
        }
        break;
    case C_RIGHT:
        if(opr == C_ON){
            deltaAngle += 0.01;
        }else if (opr == C_OFF){
           // deltaAngle += -0.01;
           deltaAngle = 0;
        }
        break;
    case C_FRONT:
        if(opr == C_ON){
            deltaMove += 0.5;
        }else if (opr == C_OFF){
            //deltaMove  -= 0.5;
            deltaMove = 0;
        }
        break;
    case C_BACK:
        if(opr == C_ON){
            deltaMove += -0.5;
        }else if (opr == C_OFF){
            //deltaMove -= -0.5;
            deltaMove = 0;
        }
        break;
    case C_UP:
        if(opr == C_ON){
            deltaY += 0.01;
        }else if (opr == C_OFF){
            deltaY = 0;
        }
        break;
    case C_DOWN:
        if(opr == C_ON){
            deltaY += -0.01;
        }else if (opr == C_OFF){
            deltaY = 0;
        }
        break;
    case C_JMP:
        if(deltaJmp == 0)
            deltaJmp = 1.0f;
        break;
    }
}

void Camera::rotate(){
    angleXZ += deltaAngle;
    lookX = sin(angleXZ);
    lookZ = -cos(angleXZ);
}

void Camera::changePerspective(){

    angleY += deltaY;

    angleY = angleY > 0.8 ? 0.8 : angleY;
    angleY = angleY < -0.8 ? -0.8 : angleY;
    lookY = sin(angleY);

}
void Camera::jump(){
    if(deltaJmp > 0.02){
        jmpHeight = -12 * (deltaJmp - 0.5) * (deltaJmp - 0.5) + 3;
        deltaJmp -= 0.01;
    }else{
        deltaJmp = 0;
    }
}
void Camera::continueMoving(){
    if(deltaMove){
        move();
    }
    if(deltaAngle){
        rotate();
    }
    if(deltaY){
        changePerspective();
    }
    if(deltaJmp){
        jump();
    }
}

GLdouble Camera::get(char axis){
	switch (axis){
	case 'x':
		return x;
	case 'y':
        return y;
	case 'z': 
		return z;
	default:
		return 1 << 20;
	}
}

GLdouble Camera::getLook(char axis){
	switch (axis){
	case 'x':
		return lookX;
	case 'y':
        return lookY;
	case 'z': 
		return lookZ;
	default:
		return 1 << 20;
	}
}

double Camera::getJmpHeight(){
    return jmpHeight;
}

void Camera::setFixArea(int rad){
	fixedRad = rad;
}


