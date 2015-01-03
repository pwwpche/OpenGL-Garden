#include "Wind.h"
#include "Calculator.h"
#include <stdlib.h>
#include <time.h>
class Flake{
public:
	Flake();
    Flake(float _x, float _y, float _z);
    void fall(Wind &wind);
    void setPosition(float _x, float _y, float _z);

    float x;
    float y;
    float z;
    Calculator cal;

};
