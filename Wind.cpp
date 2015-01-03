#include "Wind.h"

Wind::Wind(){
	x = 0;
	y = 0;
	z = 0;
}

void Wind::setLevel(float lx, float ly, float lz){
	x = lx;
	y = ly;
	z = lz;
}

Wind::Wind(float lx, float ly, float lz){
	x = lx;
	y = ly;
	z = lz;
}

float Wind::getLevelX(){
	return x;
}

float Wind::getLevelY(){
	return y;
}

float Wind::getLevelZ(){
	return z;
}

void Wind::setFallSpeed(float speed){
    speed = speed > -0.01 ? -0.01 : speed;
    speed = speed < -0.3 ? -0.3 : speed;
    y = speed;
}
