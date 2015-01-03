#include <math.h>
#ifndef CG_MYCALCULATOR
#define CG_MYCALCULATOR
class Calculator{
public:
	Calculator();
	double mysin(double angle);
	double mycos(double angle);
private:
	double sinArr[630];
	double cosArr[630];
};


#endif
