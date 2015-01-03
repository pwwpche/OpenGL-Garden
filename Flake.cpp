#include "Flake.h"

Flake::Flake(float _x, float _y, float _z)
{
	x = _x;
	y = _y;
	z = _z;
}

Flake::Flake(){
	x = 0;
	y = 0;
	z = 0;
}

void Flake::setPosition(float _x, float _y, float _z){
	x = _x;
	y = _y;
	z = _z;
}

void Flake::fall(Wind &wind){
    x += wind.x;
    y += wind.y;
    z += wind.z;
    //Noise function
    //x += (rand() % 2 == 0) ? 0.01 : -0.01;
    //z += (rand() % 2 == 0) ? 0.01 : -0.01;
	return ;
}
